#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Base Abstract Class
class DeepSeaSubmersible {
protected:
    string vesselID;
    double operationalDepthMeters;

public:
    static int activeVesselsDiving;
    static double totalSpecimenPayloadKG;

    DeepSeaSubmersible(string id, double depth)
        : vesselID(id), operationalDepthMeters(depth) {
        activeVesselsDiving++;
    }

    virtual ~DeepSeaSubmersible() {
        cout << "[SURFACED] Submersible " << vesselID << " docked at support vessel." << endl;
        activeVesselsDiving--;
    }

    // Pure Virtual Interfaces
    virtual double calculateHullIntegrityIndex() const = 0;
    virtual void transmitDiveLog() const = 0;
};

// Static definitions outside class boundary
int DeepSeaSubmersible::activeVesselsDiving = 0;
double DeepSeaSubmersible::totalSpecimenPayloadKG = 0.0;

// Derived Class 1: Trench Geological Core Sampler
class GeologicalCoreDrillSub : public DeepSeaSubmersible {
private:
    double sedimentCoreWeightKG;
    double titaniumHullThicknessMM;

public:
    GeologicalCoreDrillSub(string id, double depth, double coreWeight, double hullMM)
        : DeepSeaSubmersible(id, depth),
          sedimentCoreWeightKG(coreWeight),
          titaniumHullThicknessMM(hullMM) {
        totalSpecimenPayloadKG += coreWeight;
    }

    ~GeologicalCoreDrillSub() override {
        cout << " -> Depressurizing sediment sample chambers for " << vesselID << "..." << endl;
    }

    double calculateHullIntegrityIndex() const override {
        // Hydrostatic pressure: ~1 atm per 10m depth; thicker hull resists pressure
        double pressureAtm = operationalDepthMeters / 10.0;
        double stressRatio = pressureAtm / titaniumHullThicknessMM;
        double integrity = 100.0 - (stressRatio * 2.5);
        return (integrity < 0.0) ? 0.0 : integrity;
    }

    void transmitDiveLog() const override {
        cout << "\n==============================================" << endl;
        cout << "   GEOLOGICAL RESEARCH SUB: " << vesselID << endl;
        cout << "==============================================" << endl;
        cout << "  Operational Depth    : " << fixed << setprecision(1) << operationalDepthMeters << " m" << endl;
        cout << "  Core Samples Mined   : " << sedimentCoreWeightKG << " kg" << endl;
        cout << "  Hull Thickness       : " << titaniumHullThicknessMM << " mm" << endl;
        cout << "  Hull Integrity Score : " << fixed << setprecision(2) << calculateHullIntegrityIndex() << " / 100" << endl;
        cout << "  Dive Safety Margin   : " << (calculateHullIntegrityIndex() >= 60.0 ? "WITHIN LIMITS" : "CRITICAL RISK: ASCEND") << endl;
        cout << "==============================================" << endl;
    }
};

// Derived Class 2: Hydrothermal Vent Biological Survey Drone
class VentBiologySurveySub : public DeepSeaSubmersible {
private:
    int speciesCatalogued;
    double thermalWaterTempC;

public:
    VentBiologySurveySub(string id, double depth, int speciesCount, double waterTemp)
        : DeepSeaSubmersible(id, depth),
          speciesCatalogued(speciesCount),
          thermalWaterTempC(waterTemp) {
        // Approximation: 1.5 kg per catalogued biologic container
        totalSpecimenPayloadKG += (speciesCount * 1.5);
    }

    ~VentBiologySurveySub() override {
        cout << " -> Sterilizing bio-containment seals for " << vesselID << "..." << endl;
    }

    double calculateHullIntegrityIndex() const override {
        // High hydrothermal water temperatures compound structural wear
        double thermalStress = (thermalWaterTempC > 100.0) ? (thermalWaterTempC - 100.0) * 0.15 : 0.0;
        double depthStress = (operationalDepthMeters / 1000.0) * 8.0;
        double integrity = 100.0 - (depthStress + thermalStress);
        return (integrity < 0.0) ? 0.0 : integrity;
    }

    void transmitDiveLog() const override {
        cout << "\n==============================================" << endl;
        cout << "   HYDROTHERMAL BIOLOGICAL DRONE: " << vesselID << endl;
        cout << "==============================================" << endl;
        cout << "  Operational Depth    : " << fixed << setprecision(1) << operationalDepthMeters << " m" << endl;
        cout << "  Species Documented   : " << speciesCatalogued << " specimens" << endl;
        cout << "  Vent Fluid Temp      : " << thermalWaterTempC << " °C" << endl;
        cout << "  Hull Integrity Score : " << fixed << setprecision(2) << calculateHullIntegrityIndex() << " / 100" << endl;
        cout << "  Thermal Shielding    : " << (thermalWaterTempC <= 350.0 ? "INSULATION OPTIMAL" : "COOLING DEGRADATION") << endl;
        cout << "==============================================" << endl;
    }
};

int main() {
    cout << "\n>>> MARITIME EXPEDITION TELEMETRY HUB BOOT <<<\n" << endl;

    const int FLEET_SIZE = 2;
    DeepSeaSubmersible* oceanicFleet[FLEET_SIZE];

    // Vessel 1: Trench drilling sub down at 3800m with 120mm titanium hull
    oceanicFleet[0] = new GeologicalCoreDrillSub("TITAN-DRILL-01", 3800.0, 45.8, 120.0);

    // Vessel 2: Hydrothermal vent drone at 2400m recording near 280°C plumes
    oceanicFleet[1] = new VentBiologySurveySub("VENT-SEEKER-09", 2400.0, 18, 280.0);

    // Polymorphic execution loop
    for (int i = 0; i < FLEET_SIZE; i++) {
        oceanicFleet[i]->transmitDiveLog();
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Submersibles Diving : " << DeepSeaSubmersible::activeVesselsDiving << endl;
    cout << "Total Scientific Payload   : " << fixed << setprecision(2) 
         << DeepSeaSubmersible::totalSpecimenPayloadKG << " kg" << endl;
    cout << "----------------------------------------------\n" << endl;

    cout << ">>> INITIATING SURFACE RECALL PROCEDURE <<<\n" << endl;

    // Controlled heap deallocation
    for (int i = 0; i < FLEET_SIZE; i++) {
        delete oceanicFleet[i];
        oceanicFleet[i] = nullptr;
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Submersibles Diving After Recall : " << DeepSeaSubmersible::activeVesselsDiving << endl;
    cout << "----------------------------------------------" << endl;

    return 0;
}
