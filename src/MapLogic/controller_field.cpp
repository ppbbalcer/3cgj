#include "field.h"
#include "field_impl.h"
#include "controller_field.h"

void ControllerField::AssociateField(Field * associated, bool on_up)
{
	association tmp;
	tmp.associated_field=associated;
	tmp.on_up=on_up;
	assoc_list.push_back(tmp);
}
void ControllerField::ActivateRemotes()
{
	for (assoc_list_type::iterator it = assoc_list.begin() ; 
	     it!=assoc_list.end() ; ++it) {
		association &tmp=*it;
		;
		if (tmp.on_up)
			tmp.associated_field->Activate();
		else
			tmp.associated_field->Deactivate();
	}
	
}
void ControllerField::DeactivateRemotes()
{
	association tmp;

	for (assoc_list_type::iterator it = assoc_list.begin() ; 
	     it!=assoc_list.end() ; ++it) {
		association &tmp=*it;
		;
		if (tmp.on_up)
			tmp.associated_field->Deactivate();
		else
			tmp.associated_field->Activate();
	}
}
