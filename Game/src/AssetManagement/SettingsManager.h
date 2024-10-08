#pragma once
#include "FallingSandEngine.h"

namespace FallingSandEngine {

    class SettingsManager {
    public:
        // Register a setting with a key and initial value
        template<typename T>
        static void RegisterSetting(const std::string& key, const T& value);

        // Retrieve a setting by key
        template<typename T>
        static T GetSetting(const std::string& key);

        // Update a setting value
        template<typename T>
        static void UpdateSetting(const std::string& key, const T& value);


        static void ApplySettings();

        static void SetApplyCallback(std::function<void()> callback);

    private:
        static std::unordered_map<std::string, Ref<void>> s_Settings;  // Store settings as generic references
        static std::function<void()> m_ApplyCallback;

    };
}