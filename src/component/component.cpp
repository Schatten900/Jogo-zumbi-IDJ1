#include "component/component.h"
#include "gameObject/gameObject.h"

Component::Component(GameObject& associated)
    : associated(associated) {}

Component::~Component() {}

