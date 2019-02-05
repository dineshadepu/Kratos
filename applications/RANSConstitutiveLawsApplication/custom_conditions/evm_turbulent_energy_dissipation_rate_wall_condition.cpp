//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    , KratosAppGenerator
//

// System includes


// External includes


// Include Base h
#include "custom_conditions/evm_turbulent_energy_dissipation_rate_wall_condition.h"


namespace Kratos
{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/**
 * Constructor.
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateWallCondition(IndexType NewId)
    : Condition(NewId)
{
}

/**
 * Constructor using an array of nodes
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateWallCondition(IndexType NewId, const NodesArrayType& ThisNodes)
    : Condition(NewId, ThisNodes)
{
}

/**
 * Constructor using Geometry
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateWallCondition(IndexType NewId, GeometryType::Pointer pGeometry)
    : Condition(NewId, pGeometry)
{
}

/**
 * Constructor using Properties
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateWallCondition(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties)
    : Condition(NewId, pGeometry, pProperties)
{
}

/**
 * Copy Constructor
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::EvmTurbulentEnergyDissipationRateWallCondition(EvmTurbulentEnergyDissipationRateWallCondition const& rOther)
    : Condition(rOther)
{
}

/**
 * Destructor
 */
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::~EvmTurbulentEnergyDissipationRateWallCondition() { }

///@}
///@name Operators
///@{

/// Assignment operator.
template<unsigned int TDim, unsigned int TNumNodes>
EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes> & EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::operator=(EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes> const& rOther)
{
    BaseType::operator=(rOther);
    Flags::operator =(rOther);
    // mpProperties = rOther.mpProperties;
    return *this;
}

///@}
///@name Operations
///@{

/**
 * CONDITIONS inherited from this class have to implement next
 * Create and Clone methods: MANDATORY
 */

/**
 * creates a new condition pointer
 * @param NewId: the ID of the new condition
 * @param ThisNodes: the nodes of the new condition
 * @param pProperties: the properties assigned to the new condition
 * @return a Pointer to the new condition
 */
template<unsigned int TDim, unsigned int TNumNodes>
Condition::Pointer EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::Create(
    IndexType NewId,
    NodesArrayType const& ThisNodes,
    PropertiesType::Pointer pProperties) const
{

    KRATOS_TRY
    return Kratos::make_shared<EvmTurbulentEnergyDissipationRateWallCondition>(NewId, GetGeometry().Create(ThisNodes), pProperties);
    KRATOS_CATCH("");
}

/**
 * creates a new condition pointer
 * @param NewId: the ID of the new condition
 * @param pGeom: the geometry to be employed
 * @param pProperties: the properties assigned to the new condition
 * @return a Pointer to the new condition
 */
template<unsigned int TDim, unsigned int TNumNodes>
Condition::Pointer EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::Create(
    IndexType NewId,
    GeometryType::Pointer pGeom,
    PropertiesType::Pointer pProperties) const
{

    KRATOS_TRY
    return Kratos::make_shared<EvmTurbulentEnergyDissipationRateWallCondition>(NewId, pGeom, pProperties);
    KRATOS_CATCH("");
}

/**
 * creates a new condition pointer and clones the previous condition data
 * @param NewId: the ID of the new condition
 * @param ThisNodes: the nodes of the new condition
 * @param pProperties: the properties assigned to the new condition
 * @return a Pointer to the new condition
 */
template<unsigned int TDim, unsigned int TNumNodes>
Condition::Pointer EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::Clone(IndexType NewId, NodesArrayType const& ThisNodes) const
{
    KRATOS_TRY
    return Kratos::make_shared<EvmTurbulentEnergyDissipationRateWallCondition>(NewId, GetGeometry().Create(ThisNodes), pGetProperties());
    KRATOS_CATCH("");
}

/**
 * this determines the condition equation ID vector for all conditional
 * DOFs
 * @param rResult: the condition equation ID vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::EquationIdVector(EquationIdVectorType& rResult, ProcessInfo& CurrentProcessInfo)
{
    unsigned int number_of_nodes = GetGeometry().PointsNumber();
    if (rResult.size() != number_of_nodes)
        rResult.resize(number_of_nodes, false);

      for (unsigned int i = 0; i < number_of_nodes; i++)
    rResult[i] = GetGeometry()[i].GetDof(TURBULENT_ENERGY_DISSIPATION_RATE).EquationId();


}

/**
 * determines the condition equation list of DOFs
 * @param ConditionDofList: the list of DOFs
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::GetDofList(DofsVectorType& rConditionDofList, ProcessInfo& CurrentProcessInfo)
{
    unsigned int number_of_nodes = GetGeometry().PointsNumber();
    if (rConditionDofList.size() != number_of_nodes)
        rConditionDofList.resize(number_of_nodes);

      for (unsigned int i = 0; i < number_of_nodes; i++)
    rConditionDofList[i] = GetGeometry()[i].pGetDof(TURBULENT_ENERGY_DISSIPATION_RATE);


}

/**
 * CONDITIONS inherited from this class have to implement next
 * CalculateLocalSystem, CalculateLeftHandSide and CalculateRightHandSide methods
 * they can be managed internally with a private method to do the same calculations
 * only once: MANDATORY
 */

/**
 * this is called during the assembling process in order
 * to calculate all condition contributions to the global system
 * matrix and the right hand side
 * @param rLeftHandSideMatrix: the condition left hand side matrix
 * @param rRightHandSideVector: the condition right hand side
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateLocalSystem(
    MatrixType& rLeftHandSideMatrix,
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
}

/**
 * this is called during the assembling process in order
 * to calculate the condition left hand side matrix only
 * @param rLeftHandSideMatrix: the condition left hand side matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateLeftHandSide(MatrixType& rLeftHandSideMatrix, ProcessInfo& rCurrentProcessInfo)
{
}

/**
 * this is called during the assembling process in order
 * to calculate the condition right hand side vector only
 * @param rRightHandSideVector: the condition right hand side vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateRightHandSide(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo)
{
}

/**
 * this is called during the assembling process in order
 * to calculate the first derivatives contributions for the LHS and RHS
 * @param rLeftHandSideMatrix: the condition left hand side matrix
 * @param rRightHandSideVector: the condition right hand side
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateFirstDerivativesContributions(
    MatrixType& rLeftHandSideMatrix,
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
    if (rRightHandSideVector.size() != 0)
        rRightHandSideVector.resize(0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the condition left hand side matrix for the first derivatives constributions
 * @param rLeftHandSideMatrix: the condition left hand side matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateFirstDerivativesLHS(MatrixType& rLeftHandSideMatrix, ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the condition right hand side vector for the first derivatives constributions
 * @param rRightHandSideVector: the condition right hand side vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateFirstDerivativesRHS(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo)
{
    if (rRightHandSideVector.size() != 0)
    rRightHandSideVector.resize(0, false);
}

/**
 * CONDITION inherited from this class must implement this methods
 * if they need to add dynamic condition contributions
 * note: second derivatives means the accelerations if the displacements are the dof of the analysis
 * note: time integration parameters must be set in the rCurrentProcessInfo before calling these methods
 * CalculateSecondDerivativesContributions,
 * CalculateSecondDerivativesLHS, CalculateSecondDerivativesRHS methods are : OPTIONAL
 */


/**
 * this is called during the assembling process in order
 * to calculate the second derivative contributions for the LHS and RHS
 * @param rLeftHandSideMatrix: the condition left hand side matrix
 * @param rRightHandSideVector: the condition right hand side
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateSecondDerivativesContributions(
    MatrixType& rLeftHandSideMatrix,
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
    if (rRightHandSideVector.size() != 0)
        rRightHandSideVector.resize(0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the condition left hand side matrix for the second derivatives constributions
 * @param rLeftHandSideMatrix: the condition left hand side matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateSecondDerivativesLHS(
    MatrixType& rLeftHandSideMatrix,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rLeftHandSideMatrix.size1() != 0)
        rLeftHandSideMatrix.resize(0, 0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the condition right hand side vector for the second derivatives constributions
 * @param rRightHandSideVector: the condition right hand side vector
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateSecondDerivativesRHS(
    VectorType& rRightHandSideVector,
    ProcessInfo& rCurrentProcessInfo)
{
    if (rRightHandSideVector.size() != 0)
        rRightHandSideVector.resize(0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the condition mass matrix
 * @param rMassMatrix: the condition mass matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateMassMatrix(MatrixType& rMassMatrix, ProcessInfo& rCurrentProcessInfo)
{
    if (rMassMatrix.size1() != 0)
        rMassMatrix.resize(0, 0, false);
}

/**
 * this is called during the assembling process in order
 * to calculate the condition damping matrix
 * @param rDampingMatrix: the condition damping matrix
 * @param rCurrentProcessInfo: the current process info instance
 */
template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::CalculateDampingMatrix(MatrixType& rDampingMatrix, ProcessInfo& rCurrentProcessInfo)
{
    if (rDampingMatrix.size1() != 0)
        rDampingMatrix.resize(0, 0, false);
}

/**
 * This method provides the place to perform checks on the completeness of the input
 * and the compatibility with the problem options as well as the contitutive laws selected
 * It is designed to be called only once (or anyway, not often) typically at the beginning
 * of the calculations, so to verify that nothing is missing from the input
 * or that no common error is found.
 * @param rCurrentProcessInfo
 * this method is: MANDATORY
 */
template<unsigned int TDim, unsigned int TNumNodes>
int EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::Check(const ProcessInfo& rCurrentProcessInfo)
{
    KRATOS_TRY

    KRATOS_ERROR_IF(this->Id() < 1) <<"EvmTurbulentEnergyDissipationRateWallCondition found with Id 0 or negative" << std::endl;

    KRATOS_ERROR_IF(this->GetGeometry().Area() <= 0) << "On EvmTurbulentEnergyDissipationRateWallCondition -> "
        << this->Id() <<  "; Area cannot be less than or equal to 0" << std::endl;

    return 0;

    KRATOS_CATCH("");
}

///@}
///@name Access
///@{


///@}
///@name Inquiry
///@{


///@}
///@name Input and output
///@{

/// Turn back information as a string.

template<unsigned int TDim, unsigned int TNumNodes>
std::string EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::Info() const {
    std::stringstream buffer;
    buffer << "EvmTurbulentEnergyDissipationRateWallCondition #" << Id();
    return buffer.str();
}

/// Print information about this object.

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::PrintInfo(std::ostream& rOStream) const {
    rOStream << "EvmTurbulentEnergyDissipationRateWallCondition #" << Id();
}

/// Print object's data.

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::PrintData(std::ostream& rOStream) const {
    pGetGeometry()->PrintData(rOStream);
}

///@}
///@name Friends
///@{

///@}

///@name Protected static Member Variables
///@{

///@}
///@name Protected member Variables
///@{

///@}
///@name Protected Operators
///@{

///@}
///@name Protected Operations
///@{

///@}
///@name Protected  Access
///@{

///@}
///@name Protected Inquiry
///@{

///@}
///@name Protected LifeCycle
///@{

///@}

///@name Static Member Variables
///@{

///@}
///@name Member Variables
///@{

///@}
///@name Private Operators
///@{

///@}
///@name Private Operations
///@{

///@}
///@name Serialization
///@{

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::save(Serializer& rSerializer) const {
    KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, Condition );

    // List
    // To be completed with the class member list
}

template<unsigned int TDim, unsigned int TNumNodes>
void EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>::load(Serializer& rSerializer) {
    KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, Condition );

    // List
    // To be completed with the class member list
}

///@}
///@name Private  Access
///@{

///@}
///@name Private Inquiry
///@{

///@}
///@name Un accessible methods
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

/// input stream function
template<unsigned int TDim, unsigned int TNumNodes>
inline std::istream & operator >> (std::istream& rIStream, EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>& rThis);

/// output stream function
template<unsigned int TDim, unsigned int TNumNodes>
inline std::ostream & operator << (std::ostream& rOStream, const EvmTurbulentEnergyDissipationRateWallCondition<TDim, TNumNodes>& rThis) {
    rThis.PrintInfo(rOStream);
    rOStream << " : " << std::endl;
    rThis.PrintData(rOStream);
    return rOStream;
}

// Class template instantiation

template class EvmTurbulentEnergyDissipationRateWallCondition<2, 2>;
template class EvmTurbulentEnergyDissipationRateWallCondition<3, 3>;

} // namespace Kratos.