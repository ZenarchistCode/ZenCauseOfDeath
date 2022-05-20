modded class EmoteManager
{
	override void KillPlayer()
	{
		super.KillPlayer();
		m_Player.m_CauseOfDeath = GetCauseOfDeathConfig().GetCauseOfDeath("suicide").CauseMessage;
	};
};