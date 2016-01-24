#pragma once


// A fixed step timer class
class Timer
{
public:
    Timer(float targetFPS) { Reset(targetFPS); }

    void Reset(float targetFPS)
    {
        glfwSetTime(0.0);
        m_leftOver = m_lastTime = m_totalTime = 0.0;
        m_secondCounter = m_fps = m_frameCounter = 0;
        m_target = 1.0 / targetFPS;
    }

    // TODO: void SetMaxFPS(float maxFPS) { m_maxFPS = maxFPS; }

    unsigned int GetFPS() { return m_fps; }

    void Update(std::function<void(float)> update) 
    {
        // Get current and delta time
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        // Second counter keeps track whether we have crossed a second
        m_secondCounter += (unsigned int)(deltaTime * 10000000);

        if (deltaTime > 1.0)
            deltaTime = 1.0;

        // stop accumulation of small error
        if (abs(deltaTime - m_target) < 1.0 / 4000.0f)
            deltaTime = m_target;

        m_leftOver += deltaTime;
        // We have passed one more frame this second
        if (m_leftOver >= m_target)
            ++m_frameCounter;

        // Update as much as the "fix-steps" have passed
        while (m_leftOver >= m_target)
        {
            m_totalTime += m_target;
            m_leftOver -= m_target;
            update((float)m_target);
        }

        // Calculate FPS using frameCounter and secondCounter
        if (m_secondCounter >= 10000000)
        {
            m_fps = m_frameCounter;
            m_frameCounter = 0;
            m_secondCounter %= 10000000;
        }
    }

private:
    double m_lastTime, m_target, m_leftOver, m_totalTime;
    unsigned int m_fps, m_frameCounter, m_secondCounter;
};
