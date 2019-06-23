#include "Mutator.h"

namespace APGG {
    class ThresholdMutator : public Mutator
    {
    protected:
        float m_threshold = 0.2;
    public:

        void setThreshold(const float threshold);
        void mutate(const std::vector<rOrganism>& selection);
    };
}
