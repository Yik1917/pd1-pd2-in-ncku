#include <string>
#include <vector>

class UserInfo {
    private:
        std::string name;
        int id;
    public:
        UserInfo(std::string name, int id); 
        std::string getName() const { return name;  }
        int getId() const { return id; }
};
class Mansion {
    public:
        virtual int printMagicNumber(int target);
        virtual int printMagicNumber();
        virtual bool addUser(const UserInfo& user, const std::string& parent);
        virtual ~Mansion() = default;
};
class RongGuoMansion : public Mansion {
    private:
        std::vector<std::pair<UserInfo,UserInfo>> users;   
        // first: 自己, second 父親或母親
    public:
        virtual int printMagicNumber(int target);
        virtual int printMagicNumber();
        virtual bool addUser(const UserInfo& user, const std::string& parent);
};
class NingGuoMansion : public Mansion {
    private:
        std::vector<std::pair<UserInfo,UserInfo>> users;
        // first: 自己, second 父親或母親
    public:
        virtual int printMagicNumber(int target);
        virtual int printMagicNumber();
        virtual bool addUser(const UserInfo& user, const std::string& parent);
        std::string printLCA(std::string name1, std::string name2);
};
class UserManager : public RongGuoMansion, public NingGuoMansion {
    public:
        bool addUser(const UserInfo& user, const std::string& parent, const std::string& type);
};

