#include <iostream>
#include "dim/dis.hxx"
#include "dim/dim.h"




int main()
{
	std::cout << "Hello CMake." << std::endl;

	char node_name[132];
	get_node_name(node_name);

	std::cout << "DNS launched at node " << node_name << std::endl;

	return 0;
}
