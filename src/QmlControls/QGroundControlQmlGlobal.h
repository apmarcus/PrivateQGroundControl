/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Don Gagne <don@thegagnes.com>

#ifndef QGroundControlQmlGlobal_H
#define QGroundControlQmlGlobal_H

#include "QGCToolbox.h"
#include "QGCApplication.h"
#include "LinkManager.h"
#include "SettingsFact.h"
#include "FactMetaData.h"
#include "SimulatedPosition.h"
#include "QGCLoggingCategory.h"
#include "AppSettings.h"
#include "AirspaceManager.h"
#include "ADSBVehicleManager.h"
#if defined(QGC_ENABLE_PAIRING)
#include "PairingManager.h"
#endif
#if defined(QGC_GST_TAISYNC_ENABLED)
#include "TaisyncManager.h"
#else
class TaisyncManager;
#endif
#if defined(QGC_GST_MICROHARD_ENABLED)
#include "MicrohardManager.h"
#else
class MicrohardManager;
#endif

#ifdef QT_DEBUG
#include "MockLink.h"
#endif

class QGCToolbox;

class QGroundControlQmlGlobal : public QGCTool
{
    Q_OBJECT

public:
    QGroundControlQmlGlobal(QGCApplication* app, QGCToolbox* toolbox);
    ~QGroundControlQmlGlobal();

    /**
     * Additions by Aaron Marcus for MouseHUD
     */
    enum MouseHUDMode {
        Mouse_GPS_Position,
        GCS_GPS_Position,
        FlightMapCenter,
        FlightMapZoom
    };
    Q_ENUM(MouseHUDMode)
    Q_PROPERTY(MouseHUDMode mouseHUDMode READ mouseHUDMode WRITE setMouseHUDMode NOTIFY mouseHUDModeChanged )
    //**Accessors
    MouseHUDMode    mouseHUDMode(void) const {return _mouseHUDMode;}
    void setMouseHUDMode(QGroundControlQmlGlobal::MouseHUDMode mouseHUDMode);

    //**Functions
    Q_INVOKABLE void advanceMouseHUDMode();

    //******* End Additions by Aaron Marcus for MouseHUD **********

    enum AltitudeMode {
        AltitudeModeNone,           // Being used as distance value unrelated to ground (for example distance to structure)
        AltitudeModeRelative,       // MAV_FRAME_GLOBAL_RELATIVE_ALT
        AltitudeModeAbsolute,       // MAV_FRAME_GLOBAL
        AltitudeModeAboveTerrain,   // Absolute altitude above terrain calculated from terrain data
        AltitudeModeTerrainFrame    // MAV_FRAME_GLOBAL_TERRAIN_ALT
    };
    Q_ENUM(AltitudeMode)

    Q_PROPERTY(QString              appName             READ appName                CONSTANT)

    Q_PROPERTY(LinkManager*         linkManager         READ linkManager            CONSTANT)
    Q_PROPERTY(MultiVehicleManager* multiVehicleManager READ multiVehicleManager    CONSTANT)
    Q_PROPERTY(QGCMapEngineManager* mapEngineManager    READ mapEngineManager       CONSTANT)
    Q_PROPERTY(QGCPositionManager*  qgcPositionManger   READ qgcPositionManger      CONSTANT)
    Q_PROPERTY(MissionCommandTree*  missionCommandTree  READ missionCommandTree     CONSTANT)
    Q_PROPERTY(VideoManager*        videoManager        READ videoManager           CONSTANT)
    Q_PROPERTY(MAVLinkLogManager*   mavlinkLogManager   READ mavlinkLogManager      CONSTANT)
    Q_PROPERTY(QGCCorePlugin*       corePlugin          READ corePlugin             CONSTANT)
    Q_PROPERTY(SettingsManager*     settingsManager     READ settingsManager        CONSTANT)
    Q_PROPERTY(FactGroup*           gpsRtk              READ gpsRtkFactGroup        CONSTANT)
    Q_PROPERTY(AirspaceManager*     airspaceManager     READ airspaceManager        CONSTANT)
    Q_PROPERTY(ADSBVehicleManager*  adsbVehicleManager  READ adsbVehicleManager     CONSTANT)
    Q_PROPERTY(bool                 airmapSupported     READ airmapSupported        CONSTANT)
    Q_PROPERTY(TaisyncManager*      taisyncManager      READ taisyncManager         CONSTANT)
    Q_PROPERTY(bool                 taisyncSupported    READ taisyncSupported       CONSTANT)
    Q_PROPERTY(MicrohardManager*    microhardManager    READ microhardManager       CONSTANT)
    Q_PROPERTY(bool                 microhardSupported  READ microhardSupported     CONSTANT)
    Q_PROPERTY(bool                 supportsPairing     READ supportsPairing        CONSTANT)
#if defined(QGC_ENABLE_PAIRING)
    Q_PROPERTY(PairingManager*      pairingManager      READ pairingManager         CONSTANT)
#endif
    Q_PROPERTY(int      supportedFirmwareCount          READ supportedFirmwareCount CONSTANT)
    Q_PROPERTY(int      supportedVehicleCount           READ supportedVehicleCount  CONSTANT)
    Q_PROPERTY(bool     px4ProFirmwareSupported         READ px4ProFirmwareSupported CONSTANT)
    Q_PROPERTY(int      apmFirmwareSupported            READ apmFirmwareSupported   CONSTANT)

    Q_PROPERTY(qreal zOrderTopMost              READ zOrderTopMost              CONSTANT) ///< z order for top most items, toolbar, main window sub view
    Q_PROPERTY(qreal zOrderWidgets              READ zOrderWidgets              CONSTANT) ///< z order value to widgets, for example: zoom controls, hud widgetss
    Q_PROPERTY(qreal zOrderMapItems             READ zOrderMapItems             CONSTANT)
    Q_PROPERTY(qreal zOrderVehicles             READ zOrderVehicles             CONSTANT)
    Q_PROPERTY(qreal zOrderWaypointIndicators   READ zOrderWaypointIndicators   CONSTANT)
    Q_PROPERTY(qreal zOrderTrajectoryLines      READ zOrderTrajectoryLines      CONSTANT)
    Q_PROPERTY(qreal zOrderWaypointLines        READ zOrderWaypointLines        CONSTANT)

    //-------------------------------------------------------------------------
    // MavLink Protocol
    Q_PROPERTY(bool     isVersionCheckEnabled   READ isVersionCheckEnabled      WRITE setIsVersionCheckEnabled      NOTIFY isVersionCheckEnabledChanged)
    Q_PROPERTY(int      mavlinkSystemID         READ mavlinkSystemID            WRITE setMavlinkSystemID            NOTIFY mavlinkSystemIDChanged)
    Q_PROPERTY(bool     hasAPMSupport           READ hasAPMSupport              CONSTANT)
    Q_PROPERTY(bool     hasMAVLinkInspector     READ hasMAVLinkInspector        CONSTANT)

    Q_PROPERTY(QGeoCoordinate flightMapPosition     READ flightMapPosition      WRITE setFlightMapPosition          NOTIFY flightMapPositionChanged)
    Q_PROPERTY(double         flightMapZoom         READ flightMapZoom          WRITE setFlightMapZoom              NOTIFY flightMapZoomChanged)
    Q_PROPERTY(double         flightMapInitialZoom  MEMBER _flightMapInitialZoom                                    CONSTANT)                               ///< Zoom level to use when either gcs or vehicle shows up for first time

    Q_PROPERTY(QString  parameterFileExtension  READ parameterFileExtension CONSTANT)
    Q_PROPERTY(QString  missionFileExtension    READ missionFileExtension   CONSTANT)
    Q_PROPERTY(QString  telemetryFileExtension  READ telemetryFileExtension CONSTANT)

    /// Returns the string for distance units which has configued by user
    Q_PROPERTY(QString appSettingsDistanceUnitsString READ appSettingsDistanceUnitsString CONSTANT)
    Q_PROPERTY(QString appSettingsAreaUnitsString READ appSettingsAreaUnitsString CONSTANT)

    Q_PROPERTY(QString qgcVersion       READ qgcVersion         CONSTANT)
    Q_PROPERTY(bool    skipSetupPage    READ skipSetupPage      WRITE setSkipSetupPage NOTIFY skipSetupPageChanged)

    Q_INVOKABLE void    saveGlobalSetting       (const QString& key, const QString& value);
    Q_INVOKABLE QString loadGlobalSetting       (const QString& key, const QString& defaultValue);
    Q_INVOKABLE void    saveBoolGlobalSetting   (const QString& key, bool value);
    Q_INVOKABLE bool    loadBoolGlobalSetting   (const QString& key, bool defaultValue);

    Q_INVOKABLE void    deleteAllSettingsNextBoot       () { _app->deleteAllSettingsNextBoot(); }
    Q_INVOKABLE void    clearDeleteAllSettingsNextBoot  () { _app->clearDeleteAllSettingsNextBoot(); }

    Q_INVOKABLE void    startPX4MockLink            (bool sendStatusText);
    Q_INVOKABLE void    startGenericMockLink        (bool sendStatusText);
    Q_INVOKABLE void    startAPMArduCopterMockLink  (bool sendStatusText);
    Q_INVOKABLE void    startAPMArduPlaneMockLink   (bool sendStatusText);
    Q_INVOKABLE void    startAPMArduSubMockLink     (bool sendStatusText);
    Q_INVOKABLE void    startAPMArduRoverMockLink   (bool sendStatusText);
    Q_INVOKABLE void    stopOneMockLink             (void);

    /// Converts from meters to the user specified distance unit
    Q_INVOKABLE QVariant metersToAppSettingsDistanceUnits(const QVariant& meters) const { return FactMetaData::metersToAppSettingsDistanceUnits(meters); }

    /// Converts from user specified distance unit to meters
    Q_INVOKABLE QVariant appSettingsDistanceUnitsToMeters(const QVariant& distance) const { return FactMetaData::appSettingsDistanceUnitsToMeters(distance); }

    QString appSettingsDistanceUnitsString(void) const { return FactMetaData::appSettingsDistanceUnitsString(); }

    /// Converts from square meters to the user specified area unit
    Q_INVOKABLE QVariant squareMetersToAppSettingsAreaUnits(const QVariant& meters) const { return FactMetaData::squareMetersToAppSettingsAreaUnits(meters); }

    /// Converts from user specified area unit to square meters
    Q_INVOKABLE QVariant appSettingsAreaUnitsToSquareMeters(const QVariant& area) const { return FactMetaData::appSettingsAreaUnitsToSquareMeters(area); }

    QString appSettingsAreaUnitsString(void) const { return FactMetaData::appSettingsAreaUnitsString(); }

    /// Returns the list of available logging category names.
    Q_INVOKABLE QStringList loggingCategories(void) const { return QGCLoggingCategoryRegister::instance()->registeredCategories(); }

    /// Turns on/off logging for the specified category. State is saved in app settings.
    Q_INVOKABLE void setCategoryLoggingOn(const QString& category, bool enable) { QGCLoggingCategoryRegister::instance()->setCategoryLoggingOn(category, enable); }

    /// Returns true if logging is turned on for the specified category.
    Q_INVOKABLE bool categoryLoggingOn(const QString& category) { return QGCLoggingCategoryRegister::instance()->categoryLoggingOn(category); }

    /// Updates the logging filter rules after settings have changed
    Q_INVOKABLE void updateLoggingFilterRules(void) { QGCLoggingCategoryRegister::instance()->setFilterRulesFromSettings(QString()); }

    Q_INVOKABLE bool linesIntersect(QPointF xLine1, QPointF yLine1, QPointF xLine2, QPointF yLine2);

    Q_INVOKABLE double degreesToRadians(double degrees) { return qDegreesToRadians(degrees); }
    Q_INVOKABLE double radiansToDegrees(double radians) { return qRadiansToDegrees(radians); }

    // Property accesors

    QString                 appName             ()  { return qgcApp()->applicationName(); }
    LinkManager*            linkManager         ()  { return _linkManager; }
    MultiVehicleManager*    multiVehicleManager ()  { return _multiVehicleManager; }
    QGCMapEngineManager*    mapEngineManager    ()  { return _mapEngineManager; }
    QGCPositionManager*     qgcPositionManger   ()  { return _qgcPositionManager; }
    MissionCommandTree*     missionCommandTree  ()  { return _missionCommandTree; }
    VideoManager*           videoManager        ()  { return _videoManager; }
    MAVLinkLogManager*      mavlinkLogManager   ()  { return _mavlinkLogManager; }
    QGCCorePlugin*          corePlugin          ()  { return _corePlugin; }
    SettingsManager*        settingsManager     ()  { return _settingsManager; }
    FactGroup*              gpsRtkFactGroup     ()  { return _gpsRtkFactGroup; }
    AirspaceManager*        airspaceManager     ()  { return _airspaceManager; }
    ADSBVehicleManager*     adsbVehicleManager  ()  { return _adsbVehicleManager; }
#if defined(QGC_ENABLE_PAIRING)
    bool                    supportsPairing     ()  { return true; }
    PairingManager*         pairingManager      ()  { return _pairingManager; }
#else
    bool                    supportsPairing     ()  { return false; }
#endif
    static QGeoCoordinate   flightMapPosition   ()  { return _coord; }
    static double           flightMapZoom       ()  { return _zoom; }

    TaisyncManager*         taisyncManager      ()  { return _taisyncManager; }
#if defined(QGC_GST_TAISYNC_ENABLED)
    bool                    taisyncSupported    ()  { return true; }
#else
    bool                    taisyncSupported    () { return false; }
#endif

    MicrohardManager*       microhardManager    () { return _microhardManager; }
#if defined(QGC_GST_TAISYNC_ENABLED)
    bool                    microhardSupported  () { return true; }
#else
    bool                    microhardSupported  () { return false; }
#endif

    qreal zOrderTopMost             () { return 1000; }
    qreal zOrderWidgets             () { return 100; }
    qreal zOrderMapItems            () { return 50; }
    qreal zOrderWaypointIndicators  () { return 50; }
    qreal zOrderVehicles            () { return 49; }
    qreal zOrderTrajectoryLines     () { return 48; }
    qreal zOrderWaypointLines       () { return 47; }

    bool    isVersionCheckEnabled   () { return _toolbox->mavlinkProtocol()->versionCheckEnabled(); }
    int     mavlinkSystemID         () { return _toolbox->mavlinkProtocol()->getSystemId(); }
#if defined(NO_ARDUPILOT_DIALECT)
    bool    hasAPMSupport           () { return false; }
#else
    bool    hasAPMSupport           () { return true; }
#endif

#if defined(QGC_ENABLE_MAVLINK_INSPECTOR)
    bool    hasMAVLinkInspector     () { return true; }
#else
    bool    hasMAVLinkInspector     () { return false; }
#endif

    int     supportedFirmwareCount  ();
    int     supportedVehicleCount   ();
    bool    px4ProFirmwareSupported ();
    bool    apmFirmwareSupported    ();
    bool    skipSetupPage           () { return _skipSetupPage; }
    void    setSkipSetupPage        (bool skip);

    void    setIsVersionCheckEnabled    (bool enable);
    void    setMavlinkSystemID          (int  id);
    void    setFlightMapPosition        (QGeoCoordinate& coordinate);
    void    setFlightMapZoom            (double zoom);

    QString parameterFileExtension  (void) const  { return AppSettings::parameterFileExtension; }
    QString missionFileExtension    (void) const    { return AppSettings::missionFileExtension; }
    QString telemetryFileExtension  (void) const  { return AppSettings::telemetryFileExtension; }

    QString qgcVersion              (void) const;

#if defined(QGC_AIRMAP_ENABLED)
    bool    airmapSupported() { return true; }
#else
    bool    airmapSupported() { return false; }
#endif

    // Overrides from QGCTool
    virtual void setToolbox(QGCToolbox* toolbox);

signals:
    void isMultiplexingEnabledChanged   (bool enabled);
    void isVersionCheckEnabledChanged   (bool enabled);
    void mavlinkSystemIDChanged         (int id);
    void flightMapPositionChanged       (QGeoCoordinate flightMapPosition);
    void flightMapZoomChanged           (double flightMapZoom);
    void skipSetupPageChanged           ();

    //****Added for MouseHUD****
    void mouseHUDModeChanged            (QGroundControlQmlGlobal::MouseHUDMode mode);
    //**************************

private:
    double                  _flightMapInitialZoom   = 17.0;
    LinkManager*            _linkManager            = nullptr;
    MultiVehicleManager*    _multiVehicleManager    = nullptr;
    QGCMapEngineManager*    _mapEngineManager       = nullptr;
    QGCPositionManager*     _qgcPositionManager     = nullptr;
    MissionCommandTree*     _missionCommandTree     = nullptr;
    VideoManager*           _videoManager           = nullptr;
    MAVLinkLogManager*      _mavlinkLogManager      = nullptr;
    QGCCorePlugin*          _corePlugin             = nullptr;
    FirmwarePluginManager*  _firmwarePluginManager  = nullptr;
    SettingsManager*        _settingsManager        = nullptr;
    FactGroup*              _gpsRtkFactGroup        = nullptr;
    AirspaceManager*        _airspaceManager        = nullptr;
    TaisyncManager*         _taisyncManager         = nullptr;
    MicrohardManager*       _microhardManager       = nullptr;
    ADSBVehicleManager*     _adsbVehicleManager     = nullptr;
#if defined(QGC_ENABLE_PAIRING)
    PairingManager*         _pairingManager         = nullptr;
#endif

    bool                    _skipSetupPage          = false;

    static const char* _flightMapPositionSettingsGroup;
    static const char* _flightMapPositionLatitudeSettingsKey;
    static const char* _flightMapPositionLongitudeSettingsKey;
    static const char* _flightMapZoomSettingsKey;

    static QGeoCoordinate   _coord;
    static double           _zoom;

    //*****Added for MouseHUD******
    QGroundControlQmlGlobal::MouseHUDMode       _mouseHUDMode;
    //*******************
};

#endif
