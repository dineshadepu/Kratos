//
//   Project Name:        KratosConstitutiveModelsApplication $
//   Created by:          $Author:                JMCarbonell $
//   Last modified by:    $Co-Author:                         $
//   Date:                $Date:                   April 2017 $
//   Revision:            $Revision:                      0.0 $
//
//

#if !defined (KRATOS_LARGE_STRAIN_3D_LAW_H_INCLUDED)
#define  KRATOS_LARGE_STRAIN_3D_LAW_H_INCLUDED

// System includes

// External includes

// Project includes
#include "custom_laws/constitutive_3D_law.hpp"
#include "custom_models/constitutive_model.hpp"

namespace Kratos
{
  /**
   * Defines a large_strain isotropic constitutive law
   * the functionality is limited to large displacements elasticity.
   */
  class KRATOS_API(CONSTITUTIVE_MODELS_APPLICATION) LargeStrain3DLaw : public Constitutive3DLaw
  {
  public:

    ///@name Type Definitions
    ///@{

    typedef ConstitutiveModel                                     ModelType; //large_strain model
    typedef ModelType::Pointer                             ModelTypePointer;

    /// Pointer definition of LargeStrain3DLaw
    KRATOS_CLASS_POINTER_DEFINITION( LargeStrain3DLaw );

    ///@}
    ///@name Life Cycle
    ///@{

    /// Default constructor.
    LargeStrain3DLaw();

    /// Constructor.
    LargeStrain3DLaw(ModelTypePointer pModel);

    /// Copy constructor.
    LargeStrain3DLaw(const LargeStrain3DLaw& rOther);

    /// Assignment operator.
    LargeStrain3DLaw& operator=(LargeStrain3DLaw const& rOther);

    /// Clone.
    ConstitutiveLaw::Pointer Clone() const override;

    /// Destructor.
    ~LargeStrain3DLaw() override;

    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{

    /**
     * Material parameters are inizialized
     */
    void InitializeMaterial(const Properties& rProperties,
			    const GeometryType& rElementGeometry,
			    const Vector& rShapeFunctionsValues ) override;

    /**
     * Computes the material response:
     * PK2 stresses and algorithmic ConstitutiveMatrix
     * @param rValues
     * @see   Parameters
     */
    void CalculateMaterialResponsePK2(Parameters & rValues) override;

    /**
     * Computes the material response:
     * Kirchhoff stresses and algorithmic ConstitutiveMatrix
     * @param rValues
     * @see   Parameters
     */
    void CalculateMaterialResponseKirchhoff (Parameters & rValues) override;


    /**
     * This function is designed to be called once to check compatibility with element
     * @param rFeatures
     */
    void GetLawFeatures(Features& rFeatures) override;


    /**
     * This function is designed to be called once to check compatibility with element and the model
     * @param rFeatures
     */
    void GetModelFeatures(Features& rFeatures);


    /**
     * This function is designed to be called once to perform all the checks needed
     * on the input provided. Checks can be "expensive" as the function is designed
     * to catch user's errors.
     * @param rProperties
     * @param rElementGeometry
     * @param rCurrentProcessInfo
     * @return
     */
    int Check(const Properties& rProperties, const GeometryType& rElementGeometry, const ProcessInfo& rCurrentProcessInfo) override;

    ///@}
    ///@name Access
    ///@{

    /**
     * Has Values
     */

    bool Has( const Variable<double>& rThisVariable ) override;

    /**
     * Set Values
     */

    void SetValue( const Variable<double>& rVariable,
                   const double& rValue,
                   const ProcessInfo& rCurrentProcessInfo ) override;

    void SetValue( const Variable<Vector>& rVariable,
                   const Vector& rValue,
                   const ProcessInfo& rCurrentProcessInfo ) override;

    void SetValue( const Variable<Matrix>& rVariable,
                   const Matrix& rValue,
                   const ProcessInfo& rCurrentProcessInfo ) override;

    /**
     * Get Values
     */

    double& GetValue( const Variable<double>& rThisVariable, double& rValue )  override;

    Matrix& GetValue( const Variable<Matrix>& rThisVariable, Matrix& rValue )  override;
    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    std::string Info() const override
    {
        std::stringstream buffer;
        buffer << "LargeStrain3DLaw";
        return buffer.str();
    }

    /// Print information about this object.
    void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << "LargeStrain3DLaw";
    }

    /// Print object's data.
    void PrintData(std::ostream& rOStream) const override
    {
      rOStream << "LargeStrain3DLaw Data";
      mpModel->PrintData(rOStream);
    }


    ///@}
    ///@name Friends
    ///@{


    ///@}


  protected:

    ///@name Protected static Member Variables
    ///@{

    ///@}
    ///@name Protected member Variables
    ///@{

    //constitutive model
    ModelTypePointer mpModel;

    //internal elastic variables

    //stored total deformation gradient for incremental strain update
    double        mTotalDeformationDet;
    MatrixType    mInverseTotalDeformationMatrix;

    ///@}
    ///@name Protected Operators
    ///@{

    ///@}
    ///@name Protected Operations
    ///@{


    /**
     * Computes the material response with model data:
     * PK2 stresses and algorithmic ConstitutiveMatrix
     * @param rValues
     * @see   Parameters
     * @param rModelValues
     */
    void CalculateMaterialResponsePK2(Parameters & rValues, ModelDataType& rModelValues) override;

    /**
     * Computes the material response with model data:
     * Kirchhoff stresses and algorithmic ConstitutiveMatrix
     * @param rValues
     * @see   Parameters
     * @param rModelValues
     */
    void CalculateMaterialResponseKirchhoff (Parameters & rValues, ModelDataType& rModelValues) override;


    /**
     * Initialize ModelData type:
     */
    void InitializeModelData(Parameters& rValues, ModelDataType& rModelValues) override;


    /**
     * Finalize ModelData type:
     */
    void FinalizeModelData(Parameters& rValues, ModelDataType& rModelValues) override;

    /**
     * Calculates the stress vector
     * matrix is to be generated for
     * @param rResult Vector the result (Stress Vector) will be stored in
     */
    virtual void CalculateStressVector(ModelDataType& rModelValues, Vector& rStressVector);


    /**
     * Calculates the constitutive matrix
     * matrix is to be generated for
     * @param rResult Matrix the result (Constitutive Matrix) will be stored in
     */
    virtual void CalculateConstitutiveMatrix(ModelDataType& rModelValues, Matrix& rConstitutiveMatrix);


    /**
     * Calculates the stress vector and constitutive matrix
     * matrix is to be generated for
     * @param rResult Vector the result (Stress Vector) will be stored in
     * @param rResult Matrix the result (ConstitutiveMatrix) will be stored in
     */
    virtual void CalculateStressVectorAndConstitutiveMatrix(ModelDataType& rModelValues, Vector& rStressVector, Matrix& rConstitutiveMatrix);


    ///@}

  private:

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
    ///@name Private  Access
    ///@{
    ///@}

    ///@}
    ///@name Serialization
    ///@{
    friend class Serializer;

    void save(Serializer& rSerializer) const override
    {
      KRATOS_SERIALIZE_SAVE_BASE_CLASS( rSerializer, Constitutive3DLaw )

      rSerializer.save("mpModel",mpModel);
      rSerializer.save("mTotalDeformationDet",mTotalDeformationDet);
      rSerializer.save("mInverseTotalDeformationMatrix",mInverseTotalDeformationMatrix);
    }

    void load(Serializer& rSerializer) override
    {
      KRATOS_SERIALIZE_LOAD_BASE_CLASS( rSerializer, Constitutive3DLaw )

      rSerializer.load("mpModel",mpModel);
      rSerializer.load("mTotalDeformationDet",mTotalDeformationDet);
      rSerializer.load("mInverseTotalDeformationMatrix",mInverseTotalDeformationMatrix);
    }


    ///@}
    ///@name Private Inquiry
    ///@{


    ///@}
    ///@name Un accessible methods
    ///@{


    ///@}
  }; // Class LargeStrain3DLaw

  ///@}

  ///@name Type Definitions
  ///@{


  ///@}
  ///@name Input and output
  ///@{

  ///@}

  ///@} addtogroup block

}  // namespace Kratos.
#endif // KRATOS_LARGE_STRAIN_3D_LAW_H_INCLUDED  defined
