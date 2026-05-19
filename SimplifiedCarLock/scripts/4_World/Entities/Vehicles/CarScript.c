modded class CarScript
{
    private bool isLocked;
    private int pinCode;

    // RPC constants
    const int RPC_SET_CODE = -3999346;
    const int RPC_TRY_TOGGLE_LOCK = -3999347;

    void CarScript()
    {
        RegisterNetSyncVariableBool("isLocked");
        // pinCode is NOT registered for security (clients shouldn't know it)
    }

    bool IsLocked() { return isLocked; }
    bool HasCode() { return pinCode > 999; }
    int GetPinCode() { return pinCode; }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (IsLocked()) return false;
        return super.CanReleaseAttachment(attachment);
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (GetGame().IsClient()) return;

        if (rpc_type == RPC_SET_CODE)
        {
            Param1<int> pSet;
            if (!ctx.Read(pSet)) return;

            if (!HasCode())
            {
                pinCode = pSet.param1;
                // pinCode is server-side only, no SetSynchDirty needed for it
            }
        }
        else if (rpc_type == RPC_TRY_TOGGLE_LOCK)
        {
            Param1<int> pTry;
            if (!ctx.Read(pTry)) return;

            // VALIDATION ON SERVER
            if (HasCode() && pTry.param1 == pinCode)
            {
                isLocked = !isLocked;
                SetSynchDirty();
            }
        }
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionInteractWithLock);
    }
}
