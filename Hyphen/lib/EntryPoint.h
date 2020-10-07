#pragma once

#ifdef _WIN64

//To be defined by the client
extern Hyphen::App * Hyphen::create();

int main(int argc, char ** argv)
{
	auto app = Hyphen::create();
	app->run();
	delete app;
}

#endif // IS_WINDOW
