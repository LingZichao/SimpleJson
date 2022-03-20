#include <bits/stdc++.h>
#include "SimpleJson.hpp"
using namespace std;

using namespace SimpleJson;
int main() {
    SimpleJson::Json j;
    j.push_back({"status" , true});
    j.push_back({"msg" , "success"});
	j.push_back({"obj" , 
		{ 
			{"name" , "ARX"} , 
			{"age" , 14 }
		} 
	});
	std::vector< SimpleJson::Object > m;
	m.push_back( { {"key" , "test1"} , {"[pos]" , 1} }) ;
    j.push_back({"data" , m} );

	std::vector<double> q {1.1 , 3.3 , 5.5, 20001128 ,-7 ,8.134};
    for(auto &it : q) {
    	printf("%lf\n" , it); //std::move之前
	}
	j.push_back({"data" , q} );
	printf("说明数据push_back后就不能使用了 , 都为一次性用品QAQ\n");
    for(auto &it : q) {
    	printf("%lf\n" , it); //std::move之后——
	}


    std::cout << j.stringize();
    printf("\nDone\n");
}

