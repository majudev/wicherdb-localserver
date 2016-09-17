#include <iostream>
#include "Database.h"

int main(int argc, char * argv[]){
	Wicher::Database::getSingleton().conn("127.0.0.1", 63431);
	if(Wicher::Database::getSingleton().login("null", "null")){
		std::cout << "GUT." << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_types()) << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("M")) << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item("M", "")) << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("M")) << std::endl;
		if(argc == 2){
            ///Creating
		    if(strcmp(argv[1], "-wz") == 0){ ///WZ
                std::vector<int> ids; ids.push_back(1); ids.push_back(1);
                std::vector<std::string> types; types.push_back("M"); types.push_back("K");
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_wz("01/01/01", "Pełesz", "", ids, types)) << std::endl;
		    }
		}else if(argc == 3){
            ///Dropping
            if(strcmp(argv[1], "-droptype") == 0){ ///Type
                if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_type("M")) << std::endl;
                }else if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_type("K")) << std::endl;
                }
		    }else if(strcmp(argv[1], "-dropwz") == 0){ ///WZ
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_wz(Wicher::Toolkit::strtoi(arg))) << std::endl;
            }else if(strcmp(argv[1], "-droppz") == 0){ ///PZ
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_pz(Wicher::Toolkit::strtoi(arg))) << std::endl;
            }else
            ///Creating
            if(strcmp(argv[1], "-item") == 0){ ///Item
                if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item("K", "Generated automatically.")) << std::endl;
                }else if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item("M", "Generated automatically.")) << std::endl;
                }
            }else if(strcmp(argv[1], "-type") == 0){ ///Type
                if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_type("M", "Materace", "")) << std::endl;
                }else if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_type("K", "Kanadyjki", "")) << std::endl;
                }
		    }else if(strcmp(argv[1], "-pz") == 0){ ///PZ
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_pz(Wicher::Toolkit::strtoi(arg), "01/01/01", "Pełesh", "")) << std::endl;
		    }else
		    ///Getting
		    if(strcmp(argv[1], "-wzitems") == 0){
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_wz_items(Wicher::Toolkit::strtoi(arg))) << std::endl;
		    }
		}else if(argc == 4){
            ///Dropping
		    if(strcmp(argv[1], "-dropitem") == 0){ ///Item
                std::string arg(argv[3]);
                if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_item(Wicher::Toolkit::strtoi(arg), "M")) << std::endl;
                }else if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_item(Wicher::Toolkit::strtoi(arg), "K")) << std::endl;
                }
		    }
		}

		std::cout << "Types:\t\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_types()) << std::endl;
		std::cout << "\"M\" Items:\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("M")) << std::endl;
		std::cout << "\"K\" Items:\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("K")) << std::endl;
		std::cout << "WZs:\t\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_wzs()) << std::endl;
		std::cout << "PZs:\t\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_pzs()) << std::endl;
		std::cout << "History:\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_history()) << std::endl;
	}
	return 0;
}
