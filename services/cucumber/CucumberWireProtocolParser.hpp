#ifndef SERVICES_CUCUMBER_WIRE_PROTOCOL_PARSER_HPP 
#define SERVICES_CUCUMBER_WIRE_PROTOCOL_PARSER_HPP

#include "services/cucumber/CucumberStepStorage.hpp"
#include "services/cucumber/CucumberContext.hpp"
#include "services/cucumber/CucumberStep.hpp"
#include "infra/stream/StringInputStream.hpp"
#include "services/cucumber/CucumberEcho.hpp"

namespace services
{
    class CucumberWireProtocolParser
    {
    public:
        CucumberWireProtocolParser(CucumberStepStorage& stepStorage);

        enum RequestType
        {
            step_matches,
            invoke,
            snippet_text,
            begin_scenario,
            end_scenario,
            invalid
        };

        enum ConditionsMatchResult
        {
            Met,
            NotMet
        };

    public:
        void ParseRequest(const infra::ByteRange& inputRange);
        void FormatResponse(infra::DataOutputStream::WithErrorPolicy& stream);
        

    private:
        CucumberStepStorage& stepStorage;

        RequestType requestType;
        ConditionsMatchResult startConditionResult;

        infra::JsonObject nameToMatch;

        uint8_t invokeId;
        infra::JsonArray invokeArguments;

        bool ContainsArguments(const infra::BoundedString& string);

        bool MatchStringArguments(infra::JsonArray& arguments);

        void SuccessMessage(infra::BoundedString& responseBuffer);
        void SuccessMessage(uint8_t id, infra::JsonArray& arguments, infra::BoundedString& responseBuffer);
        void FailureMessage(infra::BoundedString& responseBuffer, infra::BoundedConstString failMessage, infra::BoundedConstString exceptionType);

        bool InputError(infra::JsonArray& input);
        void ParseStepMatchRequest(infra::JsonArrayIterator& iteratorAtRequestType);
        void ParseInvokeRequest(infra::JsonArrayIterator& iteratorAtRequestType);
        void ParseBeginScenarioRequest();

        void FormatStepMatchResponse(infra::BoundedString& responseBuffer);
        void FormatInvokeResponse(infra::BoundedString& responseBuffer);
        void FormatSnippetResponse(infra::BoundedString& responseBuffer);
        void FormatBeginScenarioResponse(infra::BoundedString& responseBuffer);
    };
}

#endif