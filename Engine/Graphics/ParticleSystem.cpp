#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Math.h"

bleh::ParticleSystem g_particleSystem;

void bleh::ParticleSystem::Startup()
{
    m_size = 5000;
    m_particles = new Particle[m_size];
}

void bleh::ParticleSystem::Shutdown()
{
    delete[] m_particles;
}

void bleh::ParticleSystem::Update(float dt)
{
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (p->active)
        {
            p->lifetime = p->lifetime - dt;
            p->active = (p->lifetime > 0);

            p->prevPosition = p->position;
            p->position = p->position + (p->velocity * dt);
        }
    }
}

void bleh::ParticleSystem::Draw(Core::Graphics& graphics)
{
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (p->active)
        {
            graphics.SetColor(p->color);
            graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
        }
    }
}

void bleh::ParticleSystem::Create(const Vector2& position, float angle, float angleRange, size_t count, float lifetime, const Color& color, float minSpeed, float maxSpeed)
{
    for (size_t i = 0; i < count; i++)
    {
        Particle* p = GetFreeParticle();
        if (p)
        {
            p->active = true;
            p->lifetime = lifetime;
            p->position = position;
            p->prevPosition = position;
            p->color = color;

            float angleRandom = bleh::DegreesToRadians(bleh::random(-angleRange, angleRange));
            Vector2 direction = bleh::Vector2::Rotate(bleh::Vector2::forward, angle + angleRandom);
            p->velocity = direction * bleh::random(minSpeed, maxSpeed);

        }
    }
}

bleh::Particle* bleh::ParticleSystem::GetFreeParticle()
{
    for (size_t i = 0; i < m_size; i++)
    {
        Particle* p = &m_particles[i];
        if (!p->active)
        {
            return p;
        }
    }
    return nullptr;
}
