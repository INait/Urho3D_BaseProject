#include <Urho3D/Engine/Console.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/Localization.h>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/IO/FileSystem.h>

#include "config.h"
#include "stateManager/gameStateHandler.h"
#include "stateManager/gameStateEvents.h"

#include "app.h"

using namespace Urho3D;

URHO3D_DEFINE_APPLICATION_MAIN(YourProjectName)

YourProjectName::YourProjectName(Context* context) :
	Application(context)
{
	scriptedRun_ = false;
}

void YourProjectName::Setup()
{
	Configuration* config = new Configuration(context_);
	context_->RegisterSubsystem(config);
	config->Load();

	// Modify engine startup parameters
	engineParameters_["WindowTitle"] = GenerateWindowTitle();
	engineParameters_["WindowIcon"] = "Textures/appIcon.png";
	engineParameters_["LogName"] = GetSubsystem<FileSystem>()->GetAppPreferencesDir(GetTypeName(), "logs") + GetTypeName() + ".log";
	engineParameters_["FullScreen"] = config->GetValue("fullscreen").GetBool();
	engineParameters_["Borderless"] = config->GetValue("borderless").GetBool();
	engineParameters_["WindowWidth"] = config->GetValue("width").GetInt();
	engineParameters_["WindowHeight"] = config->GetValue("height").GetInt();
	engineParameters_["Sound"] = true;

	bool serverWithoutPlayer = false;
	const Vector<String>& arguments = GetArguments();
	for (auto argument : arguments)
	{
		if (argument == "-h")
		{
			engineParameters_["Headless"] = true;
		}
		else if (argument == "-s")
		{
			serverWithoutPlayer = true;
		}
	}
}

void YourProjectName::Start()
{
	// set the mouse visible
	GetSubsystem<Input>()->SetMouseVisible(true);

	// Get default style
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	XMLFile* xmlFile = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

	// Initialize localization
	Localization* l10n = GetSubsystem<Localization>();
	l10n->LoadJSONFile("Locale/StringsEnRu.json");

	Configuration* config = GetSubsystem<Configuration>();
	l10n->SetLanguage(config->GetValue("lang").GetString());

	Audio* audio = GetSubsystem<Audio>();
	if (audio)
	{
		audio->SetMasterGain("effects", config->GetValue("sound").GetFloat());
	}

	// Create console
	Console* console = engine_->CreateConsole();
	if (console)
	{
		console->SetDefaultStyle(xmlFile);
		console->GetBackground()->SetOpacity(0.8f);
	}

	// Create debug HUD.
	DebugHud* debugHud = engine_->CreateDebugHud();
	if (debugHud)
	{
		debugHud->SetDefaultStyle(xmlFile);
	}

	SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(YourProjectName, HandleKeyDown));
	SubscribeToEvent(G_STATE_EXIT_GAME, URHO3D_HANDLER(YourProjectName, HandleGameExit));

	// Create state handler
	GameStateHandler* stateHandler = new GameStateHandler(context_);
	context_->RegisterSubsystem(stateHandler);

	stateHandler->Start(GameStates::START_MAIN_MENU);
}

void YourProjectName::Stop()
{
	engine_->DumpResources(true);
}

String YourProjectName::GenerateWindowTitle() const
{
	String result =
		GetTypeName()
		+ " (" + GetPlatform() + ")"
#ifdef _WIN64
		+ " (x64)"
#else
		+ " (x86)"
#endif // _WIN64
#ifdef _DEBUG
		+ " (Debug)"
#endif // _DEBUG
		;

	return result;
}

void YourProjectName::HandleKeyDown(StringHash eventType, VariantMap & eventData)
{
	S32 qual = eventData[KeyDown::P_QUALIFIERS].GetInt();
	S32 key = eventData[KeyDown::P_KEY].GetInt();

	// ctrl + F1 toggles console
	if (key == KEY_F1 && (qual & QUAL_CTRL))
	{
		Console* console = GetSubsystem<Console>();
		console->SetVisible(!console->IsVisible());
	}

	if (qual & QUAL_CTRL)
	{
		DebugHud* debugHud = GetSubsystem<DebugHud>();
		switch (key)
		{
			case KEY_1:
				debugHud->Toggle(DEBUGHUD_SHOW_STATS);
				break;
			case KEY_2:
				debugHud->Toggle(DEBUGHUD_SHOW_MODE);
				break;
			case KEY_3:
				debugHud->Toggle(DEBUGHUD_SHOW_PROFILER);
				break;
			case KEY_4:
				debugHud->Toggle(DEBUGHUD_SHOW_MEMORY);
				break;
			case KEY_5:
				debugHud->Toggle(DEBUGHUD_SHOW_EVENTPROFILER);
				break;
		}
	}
}

void YourProjectName::HandleGameExit(StringHash eventType, VariantMap& eventData)
{
	engine_->Exit();
}
