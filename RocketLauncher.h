/*************************************************************************
Crytek Source File.
Copyright (C), Crytek Studios, 2001-2007.
-------------------------------------------------------------------------
$Id:$
$DateTime$
Description:  Class for specific rocket launcher functionality
-------------------------------------------------------------------------
History:
- 22:06:2007: Created by Benito G.R.

*************************************************************************/

#ifndef __ROCKETLAUNCHER_H__
#define __ROCKETLAUNCHER_H__

#if _MSC_VER > 1000
# pragma once
#endif
	

#include "Weapon.h"

class CRocketLauncher : public CWeapon
{
	struct EndDropAction;
	struct EndZoomOutAction;

public:
	CRocketLauncher();
	virtual ~CRocketLauncher() {};

	virtual void OnReset();
	virtual bool SetAspectProfile(EEntityAspects aspect, uint8 profile);
	virtual void Select(bool select);
	virtual void UpdateFPView(float frameTime);
	virtual void PickUp(EntityId pickerId, bool sound, bool select/* =true */, bool keepHistory/* =true */, const char *setup = NULL);
	virtual void Drop(float impulseScale, bool selectNext/* =true */, bool byDeath/* =false */);
	virtual void DropImmediate(float impulseScale, bool selectNext/* =true */, bool byDeath/* =false */);
	virtual void ProcessEvent(SEntityEvent& event);

	virtual void GetAttachmentsAtHelper(const char *helper, CCryFixedStringListT<5, 30> &attachments);

	virtual bool CanPickUp(EntityId userId) const;

	virtual void Update(SEntityUpdateContext& ctx, int);

	virtual void FullSerialize( TSerialize ser );
	virtual void PostSerialize();

	virtual void AutoDrop();
	virtual void AddFiredRocket() { m_firedRockets++; }

	virtual void OnStopFire(EntityId shooterId);

private:

	//Laser dot (FP)
	void UpdateDotEffect(float frameTime);
	void ActivateLaserDot(bool activate, bool fp);

	//Laser beam (TP) - It works more or less like LAM.cpp
	void ActivateTPLaser(bool activate);
	void UpdateTPLaser(float frameTime);
	void AttachFakeLaserToOwner(bool attach);

	void PostDropAnim();

	int		m_dotEffectSlot;
	bool	m_auxSlotUsed;
	bool  m_auxSlotUsedBQS;

	int   m_smokeEffectSlot;

	bool  m_laserTPOn;
	bool  m_laserFPOn;

	float m_lastUpdate;

	Vec3	m_lastLaserHitPt;
	bool  m_lastLaserHitSolid;
	bool  m_lastLaserHitViewPlane;
	float m_smoothLaserLength;

	int		m_firedRockets;		//Number of rockets still flying

	string m_sAimdotEffect;
	string m_sAimdotFPEffect;
	string m_sEmptySmokeEffect;

	float m_LaserRange;
	float m_LaserRangeTP;
	float m_Timeout;

protected:
		virtual bool ReadItemParams(const IItemParamsNode *params);
};


#endif // __ROCKETLAUNCHER_H__
