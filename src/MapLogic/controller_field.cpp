#include "field.h"
#include "field_impl.h"
#include "controller_field.h"


void ControllerField::ActivateRemotes()
{
	if (associated_field)
		associated_field->Activate();		
}
void ControllerField::DeactivateRemotes()
{
	if (associated_field)
		associated_field->Deactivate();
}
