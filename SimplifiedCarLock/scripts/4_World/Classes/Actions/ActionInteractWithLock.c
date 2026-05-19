class ActionInteractWithLock : ActionCarDoorsOutside
{
    override string GetText()
    {
        return "Взаимодействовать с замком";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        // Check if we are interacting with a car door from the outside
        if (!super.ActionCondition(player, target, item)) return false;

        CarScript car;
        if (!CastTo(car, target.GetParent())) return false;

        return true;
    }

    override void OnStartClient(ActionData action_data)
    {
        CarScript car = CarScript.Cast(action_data.m_Target.GetParent());
        if (car && !GetGame().GetUIManager().GetMenu())
        {
            // Open our simplified UI
            GetGame().GetUIManager().ShowScriptedMenu(new CarLockUI(car), NULL);
        }
    }
}
