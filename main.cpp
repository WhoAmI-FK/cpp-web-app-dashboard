#include <Wt/WApplication.h>
#include "Dashboard.h"
int main(int argc, char** argv)
{
	Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return Wt::cpp14::make_unique<Dashboard>(env);
		});

	return 0;
}