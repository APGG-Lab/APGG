#include "Mutator.h"

namespace APGG {
    /**
    * Basic implementation of the Mutator base class that modifies Genomes of Organisms based on the Genomes of random
    * other Organisms.
    */
    class ThresholdMutator : public Mutator
    {
    protected:
        float m_threshold = 0.2f;
    public:
        void mutate(Grid& grid, const std::unordered_set<GridIndex>& selection);
        void configure(Config& config);
    };
}
