#pragma once
#include "FallingSandEngine.h"

namespace FallingSandEngine
{
    class LoadingScreenLayer : public Layer
    {
    public:
        LoadingScreenLayer();
        virtual ~LoadingScreenLayer() = default;

        virtual void OnAttach() override;  // Load assets here
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;  // Display loading message or animation

    private:
        OrthographicCamera m_Camera;  // To render the loading screen UI
        bool m_AssetsLoaded = false;
    };
}