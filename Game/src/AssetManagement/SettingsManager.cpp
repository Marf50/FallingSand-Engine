#include "SettingsManager.h"


namespace FallingSandEngine 
{

    // Initialize the settings map
    std::unordered_map<std::string, Ref<void>> SettingsManager::s_Settings;
    std::function<void()> SettingsManager::m_ApplyCallback = nullptr;

    // Register a new setting with a key and value
    template<typename T>
    void SettingsManager::RegisterSetting(const std::string& key, const T& value) {
        if (s_Settings.find(key) != s_Settings.end()) {
            FSE_WARN("Setting '{0}' already exists!", key);
            return;
        }

        s_Settings[key] = CreateRef<T>(value);
        FSE_INFO("Registered setting '{0}'", key);
    }

    // Retrieve a setting by key
    template<typename T>
    T SettingsManager::GetSetting(const std::string& key) {
        if (s_Settings.find(key) == s_Settings.end()) {
            FSE_ERROR("Setting '{0}' not found!", key);
            return T();  // Return default value of T
        }

        return *static_cast<T*>(s_Settings[key].get());
    }

    // Update the value of an existing setting
    template<typename T>
    void SettingsManager::UpdateSetting(const std::string& key, const T& value) {
        if (s_Settings.find(key) == s_Settings.end()) {
            FSE_WARN("Setting '{0}' does not exist, creating new setting.", key);
            RegisterSetting(key, value);
        }
        else {
            *static_cast<T*>(s_Settings[key].get()) = value;
            //FSE_INFO("Updated setting '{0}'", key);
        }
    }

    void SettingsManager::ApplySettings()
    {
        if (m_ApplyCallback)
        {
            m_ApplyCallback();
        }
    }

    void SettingsManager::SetApplyCallback(std::function<void()> callback)
    {
        m_ApplyCallback = callback;
    }

    // Explicit template instantiations for common types
    template void SettingsManager::RegisterSetting<int>(const std::string&, const int&);
    template void SettingsManager::RegisterSetting<float>(const std::string&, const float&);
    template void SettingsManager::RegisterSetting<bool>(const std::string&, const bool&);
    template int SettingsManager::GetSetting<int>(const std::string&);
    template float SettingsManager::GetSetting<float>(const std::string&);
    template bool SettingsManager::GetSetting<bool>(const std::string&);
    template void SettingsManager::UpdateSetting<int>(const std::string&, const int&);
    template void SettingsManager::UpdateSetting<float>(const std::string&, const float&);
    template void SettingsManager::UpdateSetting<bool>(const std::string&, const bool&);
}