modded class PlayerBase
{
	string m_CauseOfDeath = GetCauseOfDeathConfig().GetCauseOfDeath("unknown").CauseMessage;

	// Sends a text message to the client (ZenCOD_ to prevent conflicts with other mods that might use the same method SendMessage name)
	void ZenCOD_SendMessage(string message)
	{
		Param1<string> m_MessageParam = new Param1<string>("");
		if (GetGame().IsServer() && m_MessageParam && IsAlive() && message != "")
		{
			m_MessageParam.param1 = message;
			GetGame().RPCSingleParam(this, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, GetIdentity());
		}
	}

	// Registers the check COD action
	override void SetActionsRemoteTarget(out TInputActionMap InputActionMap)
	{
		AddAction(ActionCheckCauseOfDeath, InputActionMap);
		super.SetActionsRemoteTarget(InputActionMap);
	}

	// Check for death by ammo
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (GetHealth() <= 0)
		{
			string cause = "unknown";
			ammo.ToLower();

			if (ammo.Contains("falldamage"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("falldamage").CauseMessage;
			}

			if (ammo.Contains("melee"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("melee").CauseMessage;
			}

			if (ammo.Contains("zombie"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("zombie").CauseMessage;
			}

			if (ammo.Contains("bullet"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("bullet").CauseMessage;
			}

			if (ammo.Contains("explosion"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("explosion").CauseMessage;
			}

			if (ammo.Contains("grenade"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("grenade").CauseMessage;
			}

			if (ammo.Contains("landmine"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("landmine").CauseMessage;
			}

			if (ammo.Contains("transport"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("transport").CauseMessage;
			}

			if (ammo.Contains("wolf"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("wolf").CauseMessage;
			}

			if (ammo.Contains("bear"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("bear").CauseMessage;
			}

			if (ammo.Contains("firedamage"))
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("fire").CauseMessage;
			}

			// Loop through causes of death and see if a non-hardcoded one is found
			if (cause == "unknown")
			{
				foreach(CauseOfDeathDef cod : GetCauseOfDeathConfig().CauseOfDeathDefs)
				{
					string codKey = cod.AmmoType;
					codKey.ToLower();
					if (ammo.Contains(codKey))
					{
						cause = GetCauseOfDeathConfig().GetCauseOfDeath(codKey).CauseMessage;
					}
				}
			}

			// No cause found in config.
			if (cause == "unknown")
			{
				cause = GetCauseOfDeathConfig().GetCauseOfDeath("unknown").CauseMessage;
			}

			// For debugging / adding new ammo types
			if (GetCauseOfDeathConfig().DebugOn)
			{
				cause = cause + " [ammo=" + ammo + "]";
			}

			m_CauseOfDeath = cause;
		}
	}
};