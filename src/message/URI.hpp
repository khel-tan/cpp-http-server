#ifndef URI_HPP_

#define URI_HPP_

#include <string>
/**
 * @brief The URI object currently contains only the path.
 * It implements equality and a hash function so that it can
 * be mapped to a handler in an unordered map
 */
class URI {
  public:
    // TODO: This class will be safer if the default
    // constructor is deleted
    // NOTE: Default initialization
    // of the Request class depends on this constructor
    URI()
        : path_(""){

          };

    ~URI() = default;

    URI(const std::string path) : path_(path) {}

    /**
     * @brief Converts URI object to a string
     */
    std::string
    toString() const
    {
        return path_;
    }

    /**
     * @brief Makes URI hashable
     */
    struct Hash {
        /**
         * @brief Hashes the URI
         *
         * @param uri The URI we want to hash
         */
        std::size_t
        operator()(const URI &uri) const
        {
            return std::hash<std::string>{}(uri.toString());
        }
    };

    /**
     * @brief Custom equality comparison for URI
     */
    struct Equality {
        /**
         * @brief Checks if two URI objects are equal
         */
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
