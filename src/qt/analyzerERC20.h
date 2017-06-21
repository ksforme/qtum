#include <univalue.h>

extern std::string ERC20;

struct ContractMethodParams{
    bool indexed = false;
    std::string name = "";
    std::string type = "";

    bool operator!=(ContractMethodParams& cmp){
        if(cmp.indexed == indexed && cmp.name == name && cmp.type == type)
            return false;
        return true;
    }
};

struct ContractMethod{
    bool constant = false;
    bool anonymous = false;
    std::vector<ContractMethodParams> inputs;
    std::string name = "";
    std::vector<ContractMethodParams> outputs;
    bool payable = false;
    std::string type = "";

    bool equalContractMethodParams(std::vector<ContractMethodParams>& cmps1, std::vector<ContractMethodParams>& cmps2);
    bool operator!=(ContractMethod& cm);
};

class ParserAbi{

public:

    void parseAbiJSON(const std::string jsonStr);

    std::map<std::string, ContractMethod> getContractMethods() { return contractMethods; }

private:

    std::map<std::string, ContractMethod> contractMethods;
};

class AnalyzerERC20{

public:

    AnalyzerERC20() { parser.parseAbiJSON(ERC20); ERC20Methods = parser.getContractMethods(); };

    bool isERC20(const std::string& contractAbi);

private:

    std::map<std::string, ContractMethod> ERC20Methods;

    ParserAbi parser;
};