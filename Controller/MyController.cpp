#include "Controller.h"

/*
 *      Metod : Mycontroller (Constructor)
 *      Description: To intiazlize a MyController instance we must first use a view (some program interface)
 *                   to let our user control eveything, the user will chose his in and out streaming channels
 *                   and will use the view start method to work with our Controller and model parts.
 */
MyController::MyController(View *view)
{
    if (view != nullptr)
        _view = view;

    _model = new MyModel();
    _model->Attach(*this);

    _commands["dir"] = new ShowDir(_model, _view);
    _commands["generate maze"] = new GenerateMaze(_model, _view);
    _commands["display"] = new DisplayMaze(_model, _view);
    _commands["save maze"] = new SaveMaze(_model, _view);
    _commands["load maze"] = new LoadMaze(_model, _view);
    _commands["maze size"] = new MazeSize(_model, _view);
    _commands["file size"] = new FileSize(_model, _view);
    _commands["size"] = new MazeSize(_model, _view);
    _commands["solve"] = new SolveMaze(_model, _view);
    _commands["display solution"] = new DisplaySolution(_model, _view);
    _commands["exit"] = new Exit(_model, _view);
    _commands["demo"] = new DemoRun(_model);

    std::ifstream loadFile(data_file, std::ios::in | std::ios::binary);
    if (loadFile.is_open())
        _model->loadAllMazes(&loadFile);
    loadFile.close();
}

/* 
 *      Method: update
 *      Description: This method is part of the observer pattern to update the controller.
 *                   The controller is the observer and needs to decide what to do on coming updates from the observable (the model)
 */
void MyController::update(Observable &o)
{
    std::string tmp = o.getState();

    _view->getOStream() << tmp;
}

/* 
 *      Method: get
 *      Description: This method is part of the MVC and build the connection between the interface(view)
 *                   and the command that is part of the controller. 
 */
Command *MyController::get(const std::string &command)
{
    auto it = _commands.find(command);
    if (it == _commands.end())
        return nullptr;

    return it->second;
}

/* 
 *      Method: Destructor
 */

MyController::~MyController()
{
    for (auto it = _commands.begin(); it != _commands.end(); ++it)
    {
        delete it->second;
    }

    delete _model;
}