#pragma once

#include <vcclr.h> // for gcroot
#include "stdafx.h"
#include "Material.h"
#include "SceneNode.h"

using namespace irr;
using namespace System;

namespace IrrlichtLime {
namespace Scene {

class SceneNodeInheritor : public scene::ISceneNode
{
public:

	SceneNodeInheritor(scene::ISceneNode* parent, scene::ISceneManager* manager, int id=-1,
		const core::vector3df& position = core::vector3df(0),
		const core::vector3df& rotation = core::vector3df(0),
		const core::vector3df& scale = core::vector3df(1))
		: ISceneNode(parent, manager, id, position, rotation, scale)
	{
	}

	gcroot<SceneNode::RenderEventHandler^> m_renderHandler;
	virtual void render()
	{
		m_renderHandler->Invoke();
	}

	gcroot<SceneNode::RegisterSceneNodeEventHandler^> m_OnRegisterSceneNodeHandler;
	virtual void OnRegisterSceneNode()
	{
		m_OnRegisterSceneNodeHandler->Invoke();
		ISceneNode::OnRegisterSceneNode();
	}

	gcroot<SceneNode::GetBoundingBoxEventHandler^> m_getBoundingBoxHandler;
	virtual const core::aabbox3df& getBoundingBox() const
	{
		AABBox3Df^ b = m_getBoundingBoxHandler->Invoke();
		if (b != nullptr)
			return *b->m_NativeValue;
		else
			return *((core::aabbox3df*)0);
	}

	gcroot<SceneNode::GetMaterialCountEventHandler^> m_getMaterialCountHandler;
	virtual u32 getMaterialCount() const
	{
		return m_getMaterialCountHandler->Invoke();
	}

	gcroot<SceneNode::GetMaterialEventHandler^> m_getMaterialHandler;
	virtual video::SMaterial& getMaterial(u32 i)
	{
		Video::Material^ m = m_getMaterialHandler->Invoke(i);
		if (m != nullptr)
			return *m->m_NativeValue;
		else
			return *((video::SMaterial*)0);
	}

// internal:

	void AbsoluteTransformation_set(const core::matrix4& value)
	{
		AbsoluteTransformation = value;
	}

	void SceneManager_set(scene::ISceneManager* newManager)
	{
		setSceneManager(newManager);
	}
};

} // end namespace Scene
} // end namespace IrrlichtLime