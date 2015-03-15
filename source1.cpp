 //Changed from Danya Sinicin Added Recursive iterator in dir_runner
#include <iostream>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//#include "md5.h"

using namespace std;
using namespace boost::filesystem;
  class A{
        private:
                friend class boost::serialization::access;
        
                template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                        ar & a_;
                }
        
                string a_;
        
        public:
			       A(){ std::cout << "A constructed" << std::endl; }
                A(std::string a): a_(a) { std::cout << "A constructed with 'a' ==" << a << std::endl; }
                void print()
                {
                        std::cout << "a == " << a_ << std::endl;
                }
        };
             
        class B{
        private:
                friend class boost::serialization::access;
        
                template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                        ar & b_;
                }
        
                int b_;
        public:
             B(){ std::cout << "B constructed" << std::endl; }
                B(int b): b_(b) { std::cout << "B constructed with 'b' ==" << b << std::endl; }
                void print()
                {
                        std::cout << "b == " << b_ << std::endl;
                }
        };
        
        class C{
        private:
                friend class boost::serialization::access;
        
                template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                        ar & a_;
                        ar & b_;
                        ar & d_;
                }
        
                A a_;
                B b_;
                string d_;
        
        public:
                C(){  std::cout << "C constructed" << std::endl; }
                C(std::string a,int b, string d ): a_(a), b_(b), d_(d) { std::cout << "C constructed with 'd' == " << d << std::endl; }
                void print()
                {
                        std::cout << "d == " << d_ << std::endl;
                        a_.print();
                        b_.print();
                }
        };




path main_path_get(){
	cout<<"Enter path"<<endl;
	path p;
	string s;
	getline(cin, s);
	p = s;
	while (!is_directory(p)){
		cout << "Error: " << p << " is not valid path"<< endl
			<<"Enter valid path" << endl ;
		getline(cin, s);
		p = s;
	}
	return p;
} 

void dir_runner(path main_p){
	ofstream o("output.txt");
	for (recursive_directory_iterator dir_itr(main_p);
		dir_itr != recursive_directory_iterator();
		++dir_itr)
	{
		if (is_regular_file(*dir_itr)){
				path p = *dir_itr;
				cout << "create a class:" << std::endl;
                C c(p.filename().string(), file_size(p), p.string());
				boost::archive::text_oarchive oa(o);
				oa << c;
				
		}
	}
}

int main(){
	path p=main_path_get();
	dir_runner(p);
	system("pause");
	return 0;
}