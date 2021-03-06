#include "Terminal.hpp"

namespace mf
{

Terminal::Terminal()
{
	LoadCommands();
	LoadActions();
	LoadKeys();
}

Terminal::~Terminal()
{
	
}

void				Terminal::LoadCommands()
{
	mCommands.emplace("bind", (t_terminal_command){&Bind, "binds key to action", "..."});
	mCommands.emplace("unbindall", (t_terminal_command){&UnbindAll, "unbind all keys", "..."});
	mCommands.emplace("help", (t_terminal_command){&Help, "Show all commands", "..."});
	mCommands.emplace("toggle", (t_terminal_command){&Toggle, "Toggles an action on or off", "..."});
	mCommands.emplace("clear", (t_terminal_command){&Clear, "Clear terminal", "Clear the terminal output screen"});
	mCommands.emplace("execute", (t_terminal_command){&Execute, "Execute cfg file", "Execute a cfg file"});
	mCommands.emplace("cl_setdrawmode", (t_terminal_command){&SetDrawMode, "SetDrawMode", "Set drawing mode for the client renderer"});
}

void				Terminal::LoadActions()
{
	mActions["move_backward"]	=	ACTION::MOVE_BACKWARD;
	mActions["move_forward"]	=	ACTION::MOVE_FORWARD;
	mActions["move_left"]		=	ACTION::MOVE_LEFT;
	mActions["move_right"]		=	ACTION::MOVE_RIGHT;
	mActions["move_up"]			=	ACTION::MOVE_UP;
	mActions["move_down"]		=	ACTION::MOVE_DOWN;
	mActions["jump"]			=	ACTION::JUMP;
	mActions["toggle_console"]	=	ACTION::TOGGLE_CONSOLE;
	mActions["quit"]			=	ACTION::QUIT;
	mActions["submit"]			=	ACTION::SUBMIT;
}

void				Terminal::LoadKeys()
{
	mKeys["a"]					=	sf::Keyboard::A;
	mKeys["d"]					=	sf::Keyboard::D;
	mKeys["s"]					=	sf::Keyboard::S;
	mKeys["w"]					=	sf::Keyboard::W;
	mKeys["space"]				=	sf::Keyboard::Space;
	mKeys["lctrl"]				=	sf::Keyboard::LControl;
	mKeys["esc"]				=	sf::Keyboard::Escape;
	mKeys["tilde"]				=	sf::Keyboard::Tilde;
	mKeys["enter"]				=	sf::Keyboard::Return;
}

void				Terminal::LoadGUI(Window *tWindow, ResourceManager *tResourceManager, EventHandler *tEventHandler, Renderer *tRenderer)
{
	mRenderer = tRenderer;
	try
	{
		mGUI = std::unique_ptr<Container>(new Container(tWindow));
		mTextArea = std::unique_ptr<TextBox>(new TextBox(tWindow, tResourceManager, tEventHandler));
		mTextInput = std::unique_ptr<TextBox>(new TextBox(tWindow, tResourceManager, tEventHandler));
		mSubmitButton = std::unique_ptr<Button>(new Button(tWindow, tResourceManager));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	mHasGUI = true;
	mGUI->AddItem(mTextArea.get());
	mGUI->AddItem(mTextInput.get());
	mGUI->AddItem(mSubmitButton.get());
	mGUI->SetSize(800, 500);
	mGUI->SetBackground(800, 500, sf::Color(50, 50, 50, 150));
	mGUI->SetPosition(sf::Vector2f(200, 200));

	mSubmitButton->SetPlacement(mf::ContainerPlacement::RELATIVE);
	mSubmitButton->SetPosition(sf::Vector2f(695, 445));
	mSubmitButton->SetFont("assets/fonts/firacode.otf");
	mSubmitButton->SetText("Submit!");
	mSubmitButton->SetFontSize(20);
	mSubmitButton->SetScale(sf::Vector2f(4, 3));
	mSubmitButton->SetColor(sf::Color::Red);

	mTextArea->SetPlacement(mf::ContainerPlacement::RELATIVE);
	mTextArea->SetPosition(sf::Vector2f(5, 5));
	mTextArea->SetSize(sf::Vector2f(790, 435));
	mTextArea->SetBackground(sf::Color(30, 30, 30, 100));
	mTextArea->SetFontSize(15);
	mTextArea->SetAllowFocus(false);
	mTextArea->SetFont(tResourceManager->LoadFont("assets/fonts/firacode.otf"));

	mTextInput->SetPlacement(mf::ContainerPlacement::RELATIVE);
	mTextInput->SetPosition(sf::Vector2f(5, 460));
	mTextInput->SetSize(sf::Vector2f(680, 30));
	mTextInput->SetFontSize(15);
	mTextInput->SetBackground(sf::Color(30, 30, 30, 150));
	mTextInput->SetFont(tResourceManager->LoadFont("assets/fonts/firacode.otf"));
}

void				Terminal::UpdateGUI()
{
	if (!mHasGUI)
		return ;
	if (mEventHandler->GetActionState(ACTION::SUBMIT) || mSubmitButton->GetState() == mf::MouseState::CLICKED)
	{
		if (mSubmitReset && mTextInput->GetText() != "")
		{
			ProcessCommand(mTextInput->GetText());
			mTextInput->SetText("");
			mTextArea->SetText(mTextArea->GetText() + '\n');
			mSubmitReset = false;
		}
	}
	else
		mSubmitReset = true;
	mGUI->Update();
}

void				Terminal::RenderGUI()
{
	if (!mHasGUI)
		return ;
	mGUI->Draw();
}

void				Terminal::ClearInputGUI()
{
	if (!mHasGUI)
		return ;
	mTextInput->SetText("");
}

void				Terminal::UpdateOutputStringGUI(std::string tStr)
{
	if (!mTextArea)
		return ;
	mTextArea->SetText(tStr);
}



Terminal::TERMINAL_ERROR_CODE		Terminal::ProcessCommand(std::string line)
{
	char						*tmp;
	std::string					func;
	std::vector<std::string>	params;
	std::replace(line.begin(), line.end(), '\t', ' ');
	if (line.find("//") != std::string::npos)
		return (TERMINAL_ERROR_CODE::EMPTY_COMMAND);
	if (!(tmp = strdup(line.c_str())))
		return (TERMINAL_ERROR_CODE::BAD_COMMAND);
	if (!(tmp = std::strtok((tmp + line.find_first_not_of(" ")), " ")))
		return (TERMINAL_ERROR_CODE::EMPTY_COMMAND);
	func = tmp;
	tmp = std::strtok(NULL, " ");
	while (tmp)
	{
		params.push_back(tmp);
		tmp = std::strtok(NULL, " ");
	}
	free(tmp);
	if (mCommands.count(func) > 0)
		return (mCommands[func].cmnd(this, params));
	if (mHasGUI)
        UpdateOutputStringGUI(GetOutputStringGUI() + func + " is not a valid command...\n");
	return (TERMINAL_ERROR_CODE::BAD_COMMAND);
}

Terminal::TERMINAL_ERROR_CODE		Terminal::ReadFromFile(std::string path)
{
	std::ifstream			stream(path);
	std::string				line;
	TERMINAL_ERROR_CODE		success = TERMINAL_ERROR_CODE::SUCCESS;
	TERMINAL_ERROR_CODE		tmp;

	if (!stream.is_open())
		return (TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
	while (std::getline(stream, line))
	{
		if ((tmp = ProcessCommand(line)) != TERMINAL_ERROR_CODE::SUCCESS && tmp != TERMINAL_ERROR_CODE::EMPTY_COMMAND)
			success = tmp;
	}
	return (success);
}

}


