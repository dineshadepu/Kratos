#ifndef EMBEDDED_VOLUME_TOOL_H
#define EMBEDDED_VOLUME_TOOL_H
//
//   Project Name:        Kratos
//   Last Modified by:    $Author: Guillermo Casas $
//   Date:                $Date: 2012-03-08 08:56:42 $
//
//

// /* External includes */

// System includes
#include <string>
#include <iostream>
#include <stdlib.h>

// Project includes
#include "includes/model_part.h"

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

/// This class is designed to calculate the volume of closed subdomains generated by the embedded technique.
/// It requires that variable DISTANCE has been added to the model_part.
/** @author  Guillermo Casas <gcasas@cimne.upc.edu>
*/

//class EmbeddedVolumeTool
template<std::size_t TDim >
class EmbeddedVolumeTool
{
public:
    ///@name Type Definitions
    ///@{
    typedef ModelPart::NodesContainerType::iterator NodeIteratorType;
    typedef ModelPart::ElementsContainerType::iterator ElementIteratorType;
    typedef std::size_t ListIndexType;

    /// Pointer definition of EmbeddedVolumeTool
    KRATOS_CLASS_POINTER_DEFINITION(EmbeddedVolumeTool<TDim>);

    ///@}
    ///@name Life Cycle
    ///@{

    /// Default constructor.
    EmbeddedVolumeTool() {} //

    /// Destructor.
    virtual ~EmbeddedVolumeTool() {}


    ///@}
    ///@name Operators
    ///@{

    double CalculateNegativeDistanceVolume(ModelPart& rfluid_model_part)
    {

      const int n_dem_elements = rfluid_model_part.Elements().size();
      double total_volume = 0.0;

      for (int i = 0; i < n_dem_elements; i++){
          ElementIteratorType ielem = rfluid_model_part.ElementsBegin() + i;
          Geometry< Node<3> >& geom = ielem->GetGeometry();

          array_1d<double, 4> distances;
          unsigned int n_negatives = 0;

          for (unsigned int j = 0; j != 4; ++j){
              double distance = geom[j].FastGetSolutionStepValue(DISTANCE);
              distances[j] = distance;

              if (distance < 0.0){
                  ++n_negatives;
                }

            }

          if (n_negatives == 1){

              for (unsigned int j = 0; j != 4; ++j){

                  if (distances[j] < 0.0){
                      total_volume += CalculatePyramidVolume(j, geom, distances);
                      break;
                    }
                }

            }

          else if (n_negatives == 2){

              for (unsigned int j = 0; j != 3; ++j){

                  if (distances[j] < 0.0){

                      for (unsigned int k = j + 1; j != 4; ++k){

                          if (distances[k] < 0.0){
                              total_volume += CalculateHexahedronVolume(j, k, geom, distances);
                              break;

                            }

                        }

                      break;

                    }

                }

            }

          else if (n_negatives == 3){

              for (unsigned int j = 0; j != 4; ++j){

                  if (distances[j] >= 0.0){
                      total_volume += fabs(CalculateVol(geom)) - CalculatePyramidVolume(j, geom, distances);
                      break;
                    }

                }

            }

          else if (n_negatives == 4){
              total_volume += fabs(CalculateVol(geom));
            }
        }

      return total_volume;
    }

    ///@}
    ///@name Operations
    ///@{


    ///@}
    ///@name Access
    ///@{


    ///@}
    ///@name Inquiry
    ///@{


    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a stemplate<class T, std::size_t dim> tring.
    virtual std::string Info() const
    {
        return "";
    }

    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const {}

    /// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const {}


    ///@}
    ///@name Friends
    ///@{

    ///@}

protected:
    ///@name Protected static Member rVariables
    ///@{


    ///@}
    ///@name Protected member rVariables
    ///@{ template<class T, std::size_t dim>


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

private:
    ///@name Static Member rVariables
    ///@{


    ///@}
    ///@name Member rVariables
    ///@{

    //***************************************************************************************************************
    //***************************************************************************************************************

    inline double CalculateVol(Geometry<Node<3> >&geom)
    {
      return CalculateVol(geom[0].X(), geom[0].Y(), geom[0].Z(),
                          geom[1].X(), geom[1].Y(), geom[1].Z(),
                          geom[2].X(), geom[2].Y(), geom[2].Z(),
                          geom[3].X(), geom[3].Y(), geom[3].Z());
    }

    //***************************************************************************************************************
    //***************************************************************************************************************

    inline double CalculateVol(const double x0, const double y0,
                               const double x1, const double y1,
                               const double x2, const double y2)
    {
        return 0.5 * ((x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0));
    }

    //***************************************************************************************************************
    //***************************************************************************************************************

    inline double CalculateVol(const double x0, const double y0, const double z0,
                               const double x1, const double y1, const double z1,
                               const double x2, const double y2, const double z2,
                               const double x3, const double y3, const double z3)
    {
        double x10 = x1 - x0;
        double y10 = y1 - y0;
        double z10 = z1 - z0;

        double x20 = x2 - x0;
        double y20 = y2 - y0;
        double z20 = z2 - z0;

        double x30 = x3 - x0;
        double y30 = y3 - y0;
        double z30 = z3 - z0;

        double detJ = x10 * y20 * z30 - x10 * y30 * z20 +
                      y10 * z20 * x30 - y10 * x20 * z30 +
                      z10 * x20 * y30 - z10 * y20 * x30;

        return  detJ * 0.1666666666666666666667;
    }

    //***************************************************************************************************************
    //***************************************************************************************************************

    inline double CalculatePyramidVolume(const unsigned int j, // tip of the pyramid
                                         const Geometry<Node<3> >&geom,
                                         const array_1d<double, 4>& signed_dist) // nodal signed distances
    {
      array_1d<array_1d<double, 3>, 4 > coor; // coordinates of the pyramid vertices
      array_1d<double, 4> dist;

      for (unsigned int i = 0; i != 4; ++i){
          dist[i] = fabs(signed_dist[i]);
        }

      for (unsigned int i = 0; i != 4; ++i){

          if (i == j){
              coor[i][0] = geom[j].X();
              coor[i][1] = geom[j].Y();
              coor[i][2] = geom[j].Z();
            }

          else { // for each edge, the weight of one end's coordinates is proportional to the absolut value of the signed distance of the other
              double sum_d_inv = 1 / (dist[i] + dist[j]);
              coor[i][0] = (geom[i].X() * dist[j] + geom[j].X() * dist[i]) * sum_d_inv;
              coor[i][1] = (geom[i].Y() * dist[j] + geom[j].Y() * dist[i]) * sum_d_inv;
              coor[i][2] = (geom[i].Z() * dist[j] + geom[j].Z() * dist[i]) * sum_d_inv;
            }

        }

      return fabs(CalculateVol(coor[0][0], coor[0][1], coor[0][2],
                               coor[1][0], coor[1][1], coor[1][2],
                               coor[2][0], coor[2][1], coor[2][2],
                               coor[3][0], coor[3][1], coor[3][2]));
    }

    //***************************************************************************************************************
    //***************************************************************************************************************

    inline double CalculateHexahedronVolume(const unsigned int j, // first node included in the volume
                                            const unsigned int k, // second node included in the volume
                                            const Geometry<Node<3> >&geom,
                                            const array_1d<double, 4>& signed_dist) // nodal signed distances
    {
      array_1d<array_1d<double, 3>, 4 > coor; // coordinates of the intersections
      array_1d<double, 4> dist;

      for (unsigned int i = 0; i != 4; ++i){
          dist[i] = fabs(signed_dist[i]);
        }

      double sub_volume = 0.0;
      unsigned int d = 0;

      for (unsigned int i = 0; i != 4; ++i){

          if (i != j && i != k){
              double sum_d_j_inv = 1 / (dist[i] + dist[j]);
              double sum_d_k_inv = 1 / (dist[i] + dist[k]);
              coor[d][0]     = (geom[i].X() * dist[j] + geom[j].X() * dist[i]) * sum_d_j_inv;
              coor[d][1]     = (geom[i].Y() * dist[j] + geom[j].Y() * dist[i]) * sum_d_j_inv;
              coor[d][2]     = (geom[i].Z() * dist[j] + geom[j].Z() * dist[i]) * sum_d_j_inv;
              coor[d + 1][0] = (geom[i].X() * dist[k] + geom[k].X() * dist[i]) * sum_d_k_inv;
              coor[d + 1][1] = (geom[i].Y() * dist[k] + geom[k].Y() * dist[i]) * sum_d_k_inv;
              coor[d + 1][2] = (geom[i].Z() * dist[k] + geom[k].Z() * dist[i]) * sum_d_k_inv;
              d += 2;
            }

        }

        sub_volume += fabs(CalculateVol(geom[j].X(), geom[j].Y(), geom[j].Z(),
                                        coor[1][0], coor[1][1], coor[1][2],
                                        coor[2][0], coor[2][1], coor[2][2],
                                        coor[3][0], coor[3][1], coor[3][2]));

        sub_volume += fabs(CalculateVol(geom[j].X(), geom[j].Y(), geom[j].Z(),
                                        coor[0][0], coor[0][1], coor[0][2],
                                        coor[1][0], coor[1][1], coor[1][2],
                                        coor[3][0], coor[3][1], coor[3][2]));

        sub_volume += fabs(CalculateVol(geom[k].X(), geom[k].Y(), geom[k].Z(),
                                        coor[0][0], coor[0][1], coor[0][2],
                                        coor[1][0], coor[1][1], coor[1][2],
                                        geom[j].X(), geom[j].Y(), geom[j].Z()));

        sub_volume += fabs(CalculateVol(geom[k].X(), geom[k].Y(), geom[k].Z(),
                                        coor[0][0], coor[0][1], coor[0][2],
                                        geom[j].X(), geom[j].Y(), geom[j].Z(),
                                        coor[3][0], coor[3][1], coor[3][2]));

      return sub_volume;
    }

    //***************************************************************************************************************
    //***************************************************************************************************************

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
    ///@name Private Inquiry
    ///@{


    ///@}
    ///@name Un accessible methods
    ///@{

    /// Assignment operator.
    EmbeddedVolumeTool& operator=(EmbeddedVolumeTool const& rOther);

    ///@}

}; // Class EmbeddedVolumeTool

///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{




/// output stream function
template<std::size_t TDim>
inline std::ostream& operator << (std::ostream& rOStream,
                                  const EmbeddedVolumeTool<TDim>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}


}  // namespace Kratos.

#endif // EMBEDDED_VOLUME_TOOL_H