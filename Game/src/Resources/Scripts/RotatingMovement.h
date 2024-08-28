#pragma once

/**
 * @brief Script for rotation an entity over time
 */
class RotatingMovement : public IScript {
public:
    /**
     * @param entity The entity to rotate.
     * @param rotation The rotation to apply to the entity.
     */
    explicit RotatingMovement(Entity entity, quat rotation)
        : IScript(entity), m_rotation(rotation) {
    }

protected:
    virtual void onFixedUpdate(const FixedUpdateEvent& e) override {
        auto transform = m_entity.getComponent<Transform>();
        transform->rotate(m_rotation);
    }

private:
    quat m_rotation;
};
