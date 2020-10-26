#include "Mutator.h"

namespace APGG {
    class ThresholdMutator : public Mutator
    {
    protected:
        float m_threshold = 0.2f;
    public:
        void mutate(Grid& grid, const std::unordered_set<GridIndex>& selection) override;
        void configure(Config& config) override;
    };
}
