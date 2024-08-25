#ifndef URI_HPP_

#define URI_HPP_

#include <string>
/*
 * INFO:
 * The URI object currently contains only the path.
 * It implements equality and a hash function so that it can
 * be mapped to a handler in an unordered map
 */
class URI {
  public:
    // TODO: This class will be safer if the default
    // constructor is deleted NOTE: Default initialization
    // of request depends on this constructor
    URI()
        : path_(""){

          };

    ~URI() = default;

    URI(const std::string path) : path_(path)
    {
    }

    std::string
    toString() const
    {
        return path_;
    }

    struct Hash {
        std::size_t
        operator()(const URI &uri) const
        {
            return std::hash<std::string>{}(uri.toString());
        }
    };

    struct Equality {
        bool
        operator()(const URI &lhs, const URI &rhs) const
        {
            return lhs.path_ == rhs.path_;
        }
    };

  private:
    std::string path_;
};

#endif // !DEBUG
