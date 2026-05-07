class ActionDestroyCarLockCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time;

		if (GetGame().IsClient())
		{
			time = m_ActionData.m_Player.GetUnlockDuration();
			m_ActionData.m_ActionComponent = new CAContinuousTime( time );
		}
	}
};

class ActionDestroyCarLock : ActionContinuousBase
{
	void ActionDestroyCarLock()
	{
		m_CallbackClass = ActionDestroyCarLockCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;	
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}

	override string GetText()
	{
		return "Сломать замок";
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsServer())
			return true;
	

		CarScript car;

		if ( !IsInReach(player, target, UAMaxDistances.DEFAULT) )
			return false;

		if ( Class.CastTo(car, target.GetParent()) )
		{
			return (car.HasCode() && !car.IsLogged() && !car.IsSteal() && player.HasSuitableToolForUnlock());
		}
		
		return false;
	}

	override bool ActionConditionContinue( ActionData action_data )
	{
		return true;
	}
}