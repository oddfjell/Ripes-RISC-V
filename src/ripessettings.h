#pragma once

#include <QColor>
#include <QFont>
#include <QSettings>

namespace Ripes {

// =========== Definitions of the name of all settings within Ripes ============
// User-modifyable settings
#define RIPES_SETTING_REWINDSTACKSIZE ("simulator_rewindstacksize")
#define RIPES_SETTING_CCPATH ("compiler_path")
#define RIPES_SETTING_CCARGS ("compiler_args")
#define RIPES_SETTING_LDARGS ("linker_args")
#define RIPES_SETTING_CONSOLEECHO ("console_echo")
#define RIPES_SETTING_CONSOLEBG ("console_bg_color")
#define RIPES_SETTING_CONSOLEFONTCOLOR ("console_font_color")
#define RIPES_SETTING_CONSOLEFONT ("console_font")
#define RIPES_SETTING_INDENTAMT ("editor_indent")

#define RIPES_SETTING_ASSEMBLER_TEXTSTART ("text_start")
#define RIPES_SETTING_ASSEMBLER_DATASTART ("data_start")
#define RIPES_SETTING_ASSEMBLER_BSSSTART ("bss_start")

#define RIPES_SETTING_PERIPHERALS_START ("peripheral_start")

#define RIPES_SETTING_PERIPHERAL_SETTINGS ("peripheral_settings")

// This is not really a setting, but instead a method to leverage the static observer objects that are generated for a
// setting. Used for other objects to hook into a signal emitted just before the application closes.
#define RIPES_GLOBALSIGNAL_QUIT ("sig_quit")

// Program state preserving settings
#define RIPES_SETTING_SETTING_TAB ("settings_tab")
#define RIPES_SETTING_VIEW_ZOOM ("view_zoom")
#define RIPES_SETTING_PROCESSOR_ID ("processor_id")
#define RIPES_SETTING_PROCESSOR_LAYOUT_ID ("processor_layout_id")
#define RIPES_SETTING_FOLLOW_EXEC ("follow_execution")
#define RIPES_SETTING_INPUT_TYPE ("input_type")
#define RIPES_SETTING_SOURCECODE ("sourcecode")
#define RIPES_SETTING_DARKMODE ("darkmode")

// ============= Definitions of all default settings within Ripes ==============
const extern std::map<QString, QVariant> s_defaultSettings;

/**
 * @brief The SettingObserver class
 * A wrapper class around a single Ripes setting.
 * Provides a slot for setting the setting and a signal for broadcasting that the setting was modified. Useful for
 * propagating settings changes to all over the codebase.
 */
class SettingObserver : public QObject {
    Q_OBJECT
    friend class RipesSettings;

public:
    SettingObserver(const QString& key) : m_key(key) {}
    QVariant value() const;

signals:
    void modified(const QVariant& value);

public slots:
    void setValue(const QVariant& value);

private:
    QString m_key;
};

class RipesSettings : public QSettings {
public:
    static void setValue(const QString& key, const QVariant& value);
    static QVariant value(const QString& key);

    /**
     * @brief getObserver
     * returns the observer for the given setting key @p key
     */
    static SettingObserver* getObserver(const QString& key);

private:
    static RipesSettings& get() {
        static RipesSettings inst;
        return inst;
    }
    RipesSettings();
    ~RipesSettings();

    std::map<QString, SettingObserver> m_observers;
};

}  // namespace Ripes