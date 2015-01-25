#include "field.h"
#include "field_impl.h"
#include "controller_field.h"


void ControllerField::ActivateRemotes()
{
	associated_field->Activate();		
}
void ControllerField::DeactivateRemotes()
{
	associated_field->Deactivate();
}
