#include "Terminal.hpp"

namespace mf
{
Terminal::TERMINAL_ERROR_CODE		Help(Terminal *term, std::vector<std::string> params)
{
    std::map<std::string, int>::iterator it;

    if (params.size() == 0)
    {
        for (auto const& [key, val] : term->mCommands)
        {
            std::cout << key << " : " << val.help_short << "..." << std::endl;
        }
    }
    else
    {
        std::cout << params.front() << " : " << term->mCommands[params.front()].help_long << std::endl;
    }
    (void)params;
    return (Terminal::TERMINAL_ERROR_CODE::SUCCESS);
}

Terminal::TERMINAL_ERROR_CODE		UnbindAll(Terminal *term, std::vector<std::string> params)
{
    (void)params;
    if (!term->mEventHandler)
        return (Terminal::TERMINAL_ERROR_CODE::BAD_CONTEXT);
    term->mEventHandler->UnbindAllKeys();
    return (Terminal::TERMINAL_ERROR_CODE::SUCCESS);
}

Terminal::TERMINAL_ERROR_CODE		Bind(Terminal *term, std::vector<std::string> params)
{
    if (!term->mEventHandler)
        return (Terminal::TERMINAL_ERROR_CODE::BAD_CONTEXT);
    if (params.size() < 2)
        return (Terminal::TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
    if (term->mKeys.count(params.at(0)) > 0 && term->mActions.count(params.at(1)) > 0)
        term->mEventHandler->BindKey(term->mKeys[params.at(0)], term->mActions[params.at(1)]);
    else
        return (Terminal::TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
    return(Terminal::TERMINAL_ERROR_CODE::SUCCESS);
}

Terminal::TERMINAL_ERROR_CODE		Toggle(Terminal *term, std::vector<std::string> params)
{
    if (!term->mEventHandler)
        return (Terminal::TERMINAL_ERROR_CODE::BAD_CONTEXT);
    if (params.size() == 1)
    {
        if (term->mActions.count(params.at(0)))
            term->mEventHandler->ToggleAction(term->mActions[params[0]],
                !(term->mEventHandler->GetActionState(term->mActions[params[0]])));
        else
            return (Terminal::TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
        return(Terminal::TERMINAL_ERROR_CODE::SUCCESS);
    } else if (params.size() == 2)
    {
        if (term->mActions.count(params.at(0)))
            term->mEventHandler->ToggleAction(term->mActions[params[0]], (params[1] == "0" || params[1] == "false") ? false : true);
        else
            return (Terminal::TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
        return(Terminal::TERMINAL_ERROR_CODE::SUCCESS);
    }
    return (Terminal::TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
}

}