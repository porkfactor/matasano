
// how to define this ...

// we need a set of n thunks [0 ... n)
//

// scoring
// -------------------------------------
// from a 'dictionary' (lets say some language specific text) generate a template histogram
//
// measure the weighted difference between the two. The smallest weighted difference is the
// best match.

#include <map>
#include <fstream>

namespace porkfactor
{
    namespace matasano
    {
        class ascii_histogram
        {
        public:
            ascii_histogram();

            void imbue(std::string const &path)
            {
                std::ifstream f(path);

                while(f.good())
                {
                    char c = static_cast<char>(f.get());

                    if(std::isalpha(c))
                    {
                        add(c);
                    }
                }
            }

            void clear(void)
            {
                counts_.fill(0U);
                weights_.fill(0.0f);
                total_ = 0;
            }

            void add(char c)
            {
                counts_[c]++;
                total_++;
            }

            void weigh(void)
            {
                for(size_t i = 0; i < counts_.size(); i++)
                {
                    weights_[i] = static_cast<double>(counts_[i]) / total_;
                }
            }

        private:
            size_t total_;
            std::array<size_t, 256> counts_;
            std::array<double, 256> weights_;
        };

        public operator std::ostream &
    }
}
