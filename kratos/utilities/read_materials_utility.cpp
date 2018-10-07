//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Marcelo Raschi
//                   Vicente Mataix Ferrandiz
//

// System includes

// External includes

// Project includes
#include "utilities/read_materials_utility.h"

namespace Kratos
{

ReadMaterialsUtility::ReadMaterialsUtility(Model& rModel) : mrModel(rModel)
{
}

/***********************************************************************************/
/***********************************************************************************/

ReadMaterialsUtility::ReadMaterialsUtility(
    Parameters Params,
    Model& rModel
    ) : mrModel(rModel)
{
    Parameters default_parameters(R"(
    {
        "Parameters" : {
            "materials_filename" : "please specify the file to be opened"
        }
    }  )"
    );

    Params.RecursivelyValidateAndAssignDefaults(default_parameters);

    // Read json string in materials file, create Parameters
    const std::string& materials_filename = Params["Parameters"]["materials_filename"].GetString();
    std::ifstream infile(materials_filename);
    KRATOS_ERROR_IF_NOT(infile.good()) << "Materials file: " << materials_filename << " cannot be found" << std::endl;
    std::stringstream buffer;
    buffer << infile.rdbuf();
    Parameters materials(buffer.str());

    GetPropertyBlock(materials);
}

/***********************************************************************************/
/***********************************************************************************/

ReadMaterialsUtility::ReadMaterialsUtility(
    const std::string& rParametersName,
    Model& rModel
    ) : mrModel(rModel)
{
    // Receive json string with materials properties, create Parameters
    Parameters materials(rParametersName);

    GetPropertyBlock(materials);
}

/***********************************************************************************/
/***********************************************************************************/

void ReadMaterialsUtility::ReadMaterials(Parameters Params)
{
    GetPropertyBlock(Params);
}

/***********************************************************************************/
/***********************************************************************************/

void ReadMaterialsUtility::GetPropertyBlock(Parameters Materials)
{
    KRATOS_INFO("Read materials") << "Started" << std::endl;
    for (IndexType i = 0; i < Materials["properties"].size(); ++i) {
        Parameters material = Materials["properties"].GetArrayItem(i);
        AssignPropertyBlock(material);
    }
    KRATOS_INFO("Read materials") << "Finished" << std::endl;
}

/***********************************************************************************/
/***********************************************************************************/

void ReadMaterialsUtility::TrimComponentName(std::string& rLine){
    std::stringstream ss(rLine);
    std::size_t counter = 0;
    while (std::getline(ss, rLine, '.')){++counter;}
    if (counter > 1)
        KRATOS_WARNING("Read materials") << "Ignoring module information for component " << rLine << std::endl;
}

/***********************************************************************************/
/***********************************************************************************/

void ReadMaterialsUtility::CreateProperty(
    Parameters Data,
    Properties::Pointer& pNewProperty
    )
{
    // Set the CONSTITUTIVE_LAW for the current pNewPropertyerties.
    if (Data.Has("constitutive_law")) {
        Parameters cl_parameters = Data["constitutive_law"];
        std::string constitutive_law_name = cl_parameters["name"].GetString();
        TrimComponentName(constitutive_law_name);
        cl_parameters["name"].SetString(constitutive_law_name);

        auto p_constitutive_law = KratosComponents<ConstitutiveLaw>().Get(constitutive_law_name).Create(cl_parameters);
        pNewProperty->SetValue(CONSTITUTIVE_LAW, p_constitutive_law);
    } else {
        KRATOS_INFO("Read materials") << "No constitutive law defined for material ID: " << pNewProperty->Id() << std::endl;
    }

    // Add / override the values of material parameters in the pNewPropertyerties
    Parameters variables = Data["Variables"];
    for(auto iter = variables.begin(); iter != variables.end(); ++iter) {
        const Parameters value = variables.GetValue(iter.name());

        std::string variable_name = iter.name();
        TrimComponentName(variable_name);

        // We don't just copy the values, we do some tyransformation depending of the destination variable
        if(KratosComponents<Variable<double> >::Has(variable_name)) {
            const Variable<double>& variable = KratosComponents<Variable<double>>().Get(variable_name);
            if (!value.IsNull())
                pNewProperty->SetValue(variable, value.GetDouble());
        } else if(KratosComponents<Variable<bool> >::Has(variable_name)) {
            const Variable<bool>& variable = KratosComponents<Variable<bool>>().Get(variable_name);
            if (!value.IsNull())
                pNewProperty->SetValue(variable, value.GetBool());
        } else if(KratosComponents<Variable<int> >::Has(variable_name)) {
            const Variable<int>& variable = KratosComponents<Variable<int>>().Get(variable_name);
            if (!value.IsNull())
                pNewProperty->SetValue(variable, value.GetInt());
        } else if(KratosComponents<Variable<array_1d<double, 3> > >::Has(variable_name)) {
            const Variable<array_1d<double, 3>>& variable = KratosComponents<Variable<array_1d<double, 3>>>().Get(variable_name);
            if (!value.IsNull()) {
                array_1d<double, 3> temp(3, 0.0);
                const Vector& value_variable = value.GetVector();
                KRATOS_ERROR_IF(value_variable.size() != 3) << "The vector of variable " << variable_name << " has size " << value_variable.size() << " and it is supposed to be 3" << std::endl;
                for (IndexType index = 0; index < 3; ++index)
                    temp[index] = value_variable[index];
                pNewProperty->SetValue(variable, temp);
            }
        } else if(KratosComponents<Variable<array_1d<double, 6> > >::Has(variable_name)) {
            const Variable<array_1d<double, 6>>& variable = KratosComponents<Variable<array_1d<double, 6>>>().Get(variable_name);
            if (!value.IsNull()) {
                array_1d<double, 6> temp(6, 0.0);
                const Vector& value_variable = value.GetVector();
                KRATOS_ERROR_IF(value_variable.size() != 6) << "The vector of variable " << variable_name << " has size " << value_variable.size() << " and it is supposed to be 6" << std::endl;
                for (IndexType index = 0; index < 6; ++index)
                    temp[index] = value_variable[index];
                pNewProperty->SetValue(variable, temp);
            }
        } else if(KratosComponents<Variable<Vector > >::Has(variable_name)) {
            const Variable<Vector>& variable = KratosComponents<Variable<Vector>>().Get(variable_name);
            if (!value.IsNull()) {
                pNewProperty->SetValue(variable, value.GetVector());
            }
        } else if(KratosComponents<Variable<Matrix> >::Has(variable_name)) {
            const Variable<Matrix>& variable = KratosComponents<Variable<Matrix>>().Get(variable_name);
            if (!value.IsNull()) {
                pNewProperty->SetValue(variable, value.GetMatrix());
            }
        } else if(KratosComponents<Variable<std::string> >::Has(variable_name)) {
            const Variable<std::string>& variable = KratosComponents<Variable<std::string>>().Get(variable_name);
            if (!value.IsNull()) {
                pNewProperty->SetValue(variable, value.GetString());
            }
        } else {
            KRATOS_ERROR << "Value type not defined";
        }
    }

    // Add / override tables in the pNewPropertyerties
    Parameters tables = Data["Tables"];
    for(auto iter = tables.begin(); iter != tables.end(); ++iter) {
        auto table_param = tables.GetValue(iter.name());
        // Case table is double, double. TODO(marandra): Does it make sense to consider other cases?
        Table<double> table;

        std::string input_var_name = table_param["input_variable"].GetString();
        TrimComponentName(input_var_name);
        std::string output_var_name = table_param["output_variable"].GetString();
        TrimComponentName(output_var_name);

        const auto input_var = KratosComponents<Variable<double>>().Get(input_var_name);
        const auto output_var = KratosComponents<Variable<double>>().Get(output_var_name);
        for (IndexType i = 0; i < table_param["data"].size(); ++i) {
            table.insert(table_param["data"][i][0].GetDouble(),
                         table_param["data"][i][1].GetDouble());
        }
        pNewProperty->SetTable(input_var, output_var, table);
    }
}

/***********************************************************************************/
/***********************************************************************************/

void ReadMaterialsUtility::CreateSubProperties(
    ModelPart& rModelPart,
    Parameters Data,
    Properties::Pointer& pNewProperty
    )
{
    if (Data.Has("sub_properties")) {

        PointerVectorSet<Properties, IndexedObject> list_sub_properties;

        const std::size_t number_of_subproperties = Data["sub_properties"].size();

        // We do a check of ordered ids
        IndexType counter = 1;
        for(std::size_t i_sub_prop=0; i_sub_prop < number_of_subproperties; ++i_sub_prop) {
            const int sub_property_id = Data["sub_properties"][i_sub_prop]["properties_id"].GetInt();
            KRATOS_ERROR_IF_NOT(sub_property_id == counter) << "Id's of the subproperties must be ordered and start on 1. Change your suproperties ids" << std::endl;
            ++counter;
        }

        // We assign the subproperties now
        for(std::size_t i_sub_prop=0; i_sub_prop < number_of_subproperties; ++i_sub_prop) {
            // Copy of the current parameters
            Parameters sub_prop = Data["sub_properties"][i_sub_prop];

            const int sub_property_id = sub_prop["properties_id"].GetInt();
            Properties::Pointer p_new_sub_prop = Kratos::make_shared<Properties>(sub_property_id);

            // Read the recursively subproperties
            CreateSubProperties(rModelPart, sub_prop, p_new_sub_prop);

            // We create the new sub property
            CreateProperty(sub_prop["Material"], p_new_sub_prop);

            list_sub_properties.insert(list_sub_properties.begin(), p_new_sub_prop);
        }

        pNewProperty->SetSubProperties(list_sub_properties);
    }
}

/***********************************************************************************/
/***********************************************************************************/

void ReadMaterialsUtility::AssignPropertyBlock(Parameters Data)
{
    // Get the properties for the specified model part.
    ModelPart& r_model_part = mrModel.GetModelPart(Data["model_part_name"].GetString());
    const IndexType property_id = Data["properties_id"].GetInt();
    const IndexType mesh_id = 0;
    Properties::Pointer p_prop = r_model_part.pGetProperties(property_id, mesh_id);

    // Compute the size using the iterators
    std::size_t variables_size = 0;
    for(auto it=Data["Material"]["Variables"].begin(); it!=Data["Material"]["Variables"].end(); ++it)
        ++variables_size;

    std::size_t tables_size = 0;
    for(auto it=Data["Material"]["Tables"].begin(); it!=Data["Material"]["Tables"].end(); ++it)
        ++tables_size;

    KRATOS_WARNING_IF("Read materials", variables_size > 0 && p_prop->HasVariables())
        << "Property " << std::to_string(property_id) << " already has variables." << std::endl;
    KRATOS_WARNING_IF("Read materials", tables_size > 0 && p_prop->HasTables())
        << "Property " << std::to_string(property_id) << " already has tables." << std::endl;

    // Assign the property to the model part
    r_model_part.AddProperties(p_prop);

    // Assign the p_properties to the model part's elements and conditions.
    auto& r_elements_array = r_model_part.Elements();
    auto& r_conditions_array = r_model_part.Conditions();

    #pragma omp parallel for
    for(int i = 0; i < static_cast<int>(r_elements_array.size()); ++i) {
        auto it_elem = r_elements_array.begin() + i;
        it_elem->SetProperties(p_prop);
    }

    #pragma omp parallel for
    for(int i = 0; i < static_cast<int>(r_conditions_array.size()); ++i) {
        auto it_cond = r_conditions_array.begin() + i;
        it_cond->SetProperties(p_prop);
    }

    // If the property has subproperties block we allocate this properties first
    CreateSubProperties(r_model_part, Data, p_prop);

    // We create the new property
    CreateProperty(Data["Material"], p_prop);
}

}  // namespace Kratos.
