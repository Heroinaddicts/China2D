#include "Engine.h"

UsingChina2D;

int main(int argc, const char **args, const char **env) {
	Engine::GetInstance()->AnalysisLaunchParameters(argc, args, env);

	if (Engine::GetInstance()->Launch()) {
		Engine::GetInstance()->Update();
	}
	else {
		ErrorLog(g_Engine, "Engine Launch faild");
		getchar();
	}
	return 0;
}
