modded class CarScript
{
	private bool isLocked, isLogged, isSteal;
	private int pinCode;

	private bool prevLockState;

	protected EffectSound signalAlarm;

	private ref array<string> doorSlots;

	private const string DOOR_SLOTS_RELATIVE_PATH = "CfgVehicles %1 GUIInventoryAttachmentsProps Body attachmentSlots";

	void CarScript()
	{
		RegisterNetSyncVariableBool("isLocked");
		RegisterNetSyncVariableBool("isSteal");
		RegisterNetSyncVariableInt("pinCode");

		prevLockState = IsLocked();

		isLogged = false;
	}

	bool IsLocked()
	{
		return isLocked;
	}

	bool IsSteal()
	{
		return isSteal;
	}

	bool IsLogged()
	{
		return isLogged;
	}

	bool HasCode()
	{
		return pinCode > 999;
	}

	int GetPinCode()
	{
		return pinCode;
	}

	void LogIn()
	{
		isLogged = true;
	}

	bool HasBattery()
	{
		ItemBase battery;
		if ( IsVitalCarBattery() ) 
			battery = ItemBase.Cast( FindAttachmentBySlotName("CarBattery") );
		else if ( IsVitalTruckBattery() ) 
			battery = ItemBase.Cast( FindAttachmentBySlotName("TruckBattery") );

		return battery != null;
	}

	override void OnEngineStart()
	{
		super.OnEngineStart();

		if (GetGame().IsClient())
		{
			AssignPlayer();
		}
	}

	void AssignPlayer()
	{
		PlayerBase driver = PlayerBase.Cast(GetGame().GetPlayer());

		if (!driver)
			return;

		if (CrewMemberIndex( driver ) == DayZPlayerConstants.VEHICLESEAT_DRIVER)
			driver.SetCurrentCar(this);
	}

	override bool IsInventoryVisible()
	{
		if ( !super.IsInventoryVisible() )
			return false;

		return AnyDoorOpen();
	}

	private bool AnyDoorOpen()
	{
		if (!doorSlots)
			LoadDoorSlots();
		
		if (!doorSlots || !doorSlots.Count())
			return true;

		bool anyDoorOpen;
		bool hasAnyDoor;

		CarDoorState state;

		foreach(string doorSlot : doorSlots)
		{
			state = GetCarDoorsState(doorSlot);
			switch (state)
			{
				case CarDoorState.DOORS_OPEN:
					anyDoorOpen = true;
					hasAnyDoor = true;
				break;
				case CarDoorState.DOORS_CLOSED:
					hasAnyDoor = true;
				break;
			}
		}

		if (!hasAnyDoor)
			return true;
		return anyDoorOpen;
	}

	private void LoadDoorSlots()
	{
		string doorSlotsPath = string.Format(DOOR_SLOTS_RELATIVE_PATH, GetType());

		if (GetGame().ConfigIsExisting(doorSlotsPath))
		{
			doorSlots = {};

			GetGame().ConfigGetTextArray(doorSlotsPath, doorSlots);
		}
	}

	override bool CanReleaseAttachment( EntityAI attachment )
	{
		if ( !super.CanReleaseAttachment( attachment ) )
			return false;

		if ( IsLocked() )
			return false;

		return true;
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
				
		if (prevLockState != IsLocked())
		{
			if (!IsLocked())
				PlayOpenLockSound();
			else
				PlayCloseLockSound();
			
			prevLockState = IsLocked();
		}

		if (isSteal)
		{
			PlayAlarm();
		}
	}

	void PlayOpenLockSound()
	{
		EffectSound sound =	SEffectManager.PlaySound("CARLOCK_Open_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}

	void PlayCloseLockSound()
	{
		EffectSound sound =	SEffectManager.PlaySound("CARLOCK_Close_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}

	void PlayAlarm()
	{
		if (signalAlarm && signalAlarm.IsSoundPlaying())
			return;

		signalAlarm = SEffectManager.PlaySoundOnObject("CARLOCK_Signal_SoundSet", this );
		signalAlarm.SetSoundAutodestroy( true );
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionInteractWithLockOnCarDoor);
		AddAction(ActionDirectOpenCarLock);
		AddAction(ActionDirectLockCarLock);
		
		AddAction(ActionAdminShowCarLockCode);
		AddAction(ActionAdminResetCarLockCode);
	}
}