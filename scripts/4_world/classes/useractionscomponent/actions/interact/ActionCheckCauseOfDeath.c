class ActionCheckCauseOfDeathCB : ActionContinuousBaseCB
{
    override void CreateActionComponent()
    {
        m_ActionData.m_ActionComponent = new CAContinuousTime(2);
    }
};

class ActionCheckCauseOfDeath : ActionContinuousBase
{
    void ActionCheckCauseOfDeath()
    {
        m_CallbackClass = ActionCheckCauseOfDeathCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
    }

    override typename GetInputType()
    {
        return ContinuousInteractActionInput;
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTDummy;
    }

    override string GetText()
    {
        return GetCauseOfDeathConfig().CheckCauseCommand;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        EntityAI targetEntity = EntityAI.Cast(target.GetObject());

        if (targetEntity && targetEntity.IsPlayer())
        {
            PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

            if (targetPlayer && !targetEntity.IsAlive())
                return true;
        }

        return false;
    }

    override void OnStart(ActionData action_data)
    {
        super.OnStart(action_data);
        action_data.m_Player.TryHideItemInHands(true);
    }

    override void OnEnd(ActionData action_data)
    {
        action_data.m_Player.TryHideItemInHands(false);
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

        if (!targetPlayer || !player || targetPlayer.IsAlive())
        {
            return;
        }

        string codMsg = ;
        string survivorName = GetCauseOfDeathConfig().DeadPlayerName;
        if (survivorName == "#survivorname")
        {
            survivorName = targetPlayer.GetIdentity().GetName() + "'s";
        }

        player.ZenCOD_SendMessage(GetCauseOfDeathConfig().CauseOfDeathPrefix1 + " " + survivorName + " " + GetCauseOfDeathConfig().CauseOfDeathPrefix2 + " " + targetPlayer.m_CauseOfDeath);
    }
};

// Instant version:
/*class ActionCheckCauseOfDeath : ActionInteractBase
{
    void ActionCheckCauseOfDeath()
    {
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
    }

    override string GetText()
    {
        return GetCauseOfDeathConfig().CheckCauseCommand;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        EntityAI targetEntity = EntityAI.Cast(target.GetObject());

        if (targetEntity && targetEntity.IsPlayer())
        {
            PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

            if (targetPlayer && !targetEntity.IsAlive())
                return true;
        }

        return false;
    }

    override void OnEndServer(ActionData action_data)
    {
        PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

        if (!targetPlayer || !player || targetPlayer.IsAlive())
        {
            return;
        }

        string codMsg = ;
        string survivorName = GetCauseOfDeathConfig().DeadPlayerName;
        if (survivorName == "#survivorname")
        {
            survivorName = targetPlayer.GetIdentity().GetName() + "'s";
        }

        player.ZenCOD_SendMessage(GetCauseOfDeathConfig().CauseOfDeathPrefix1 + " " + survivorName + " " + GetCauseOfDeathConfig().CauseOfDeathPrefix2 + " " + targetPlayer.m_CauseOfDeath);
    }
}*/