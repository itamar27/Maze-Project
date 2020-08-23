#include "Controller.h"

void MyController::update(Observable &o)
{
    std::string tmp = o.getState();

    _view->getOStream() << tmp;
}