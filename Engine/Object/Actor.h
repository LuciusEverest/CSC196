#pragma once
#include <Graphics\Shape.h>
#include "Graphics/Shape.h"

namespace bleh
{
	class Scene; // forward declaration

	class Actor 
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}// make sure to initialize m_transform and m_shape
		~Actor() {}
		
		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);
		
		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);
		
		virtual void OnCollision(Actor* actor) {}

		bool IsDestroyed() { return m_destroy; }
		void SetScene(Scene* scene){ m_scene = scene; }
		Transform& GetTransform() { return m_transform; } // return the transform
		Shape& GetShape() { return m_shape; }  // return the shape

	protected:
		bool m_destroy{ false };
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
	};
}