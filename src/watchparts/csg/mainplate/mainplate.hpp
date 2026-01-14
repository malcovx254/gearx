#ifndef __GEARX_MAINPLATE_H__
#define __GEARX_MAINPLATE_H__

#include <opencsg.h>
#include "displaylistPrimitive.hpp"
#include "../shapes/shape_list.hpp"

#include "../shapes/3d/shape3D.hpp"

namespace gearx {
    using namespace gearx::shape_3d;

    class MainPlate 
    // :public WatchParts, private CSGWatchObject
    { 
        private:
            float radius;
            float height;
  
            using PlateList = ShapeList<Cylinder, TruncatedCone>;
            using CutoutList = ShapeList<Cylinder, Box,TruncatedCone, ObroundCylinder>;

            &PlateList initPlateList();
            &CutoutList initCutoutList();

            float color[3];
            float innerCutoutCylinderWallColor[3];
        public:     
            PlateList plate;
            CutoutList cutout;
            

            
            MainPlate()
            :color{0.0, 0.0, 0.0}{}, innerCutoutCylinderWallColor{0.0, 0.0, 0.0}{}{
                plate = initPlateList();
                cutout = initCutoutList();
            };
            ~MainPlate() {
            }

            const float top() const {
                return 2.0;
            }
            const float base() const {
                return 0.0;
            }            

            void _render() const override {
            }
    };

    PlateList& MainPlate::initPlateList() {
        float mainTop = top();
        float mainBase = base();

            Vec2 center2D(0.0f, 0.0f);
            TruncatedCone tc1 = TruncatedCone(92.8f, 93.0f, 5.0f)
                                    .setPosition2D(center2D)
                                    .setHeightRel(mainTop, -5.0f);
            plate.add(std::move(tc1)); // 明示的にムーブして rvalue を渡す
            // center2D を取り出す（variant からの取り出しは std::get を使う）;
            Cylinder c1 = Cylinder(92.0f, 10.0f)
                                .setPosition2D(center2D)
                                .setHeightRel(std::get<TruncatedCone>(plate[plate.size()-1]).base(), -10.0f);
            plate.add(std::move(c1));
            Cylinder c2 = Cylinder(94.5f, 5.0f)
                                .setPosition2D(center2D)
                                .setHeightRel(std::get<Cylinder>(plate.atLast()).base(), -5.0f);
            plate.add(std::move(c2));
    }

    CutoutList& MainPlate::initCutoutList() {
        float mainTop = top();
        float mainBase = base();
            Vec2 center2D(-42.0f, 23.0f);
            TruncatedCone tc1_ = TruncatedCone(46.0f, 45.0f, 1.0f)
                                .setPosition2D(center2D)
                                .setHeightRel(mainTop, -1.0f);
            cutout.add(std::move(tc1_));

            Cylinder c1_ = Cylinder(45.0f, 4.0f)
                                    .setPosition2D(center2D)
                                    .setHeightRel(std::get<TruncatedCone>(cutout.atLast()).base(), -4.0f);
            cutout.add(std::move(c1_));
            TruncatedCone tc2_ = TruncatedCone(41.5f, 40.0f)
                                                .setPosition2D(center2D)
                                                .setHeightRel(std::get<Cylinder>(cutout.atLast()).base(), -1.0f);
            cutout.add(std::move(tc2_));
            Cylinder c2_ = Cylinder(40.0f, 8.0f)
                                    .setPosition2D(center2D)
                                    .setHeightRel(std::get<TruncatedCone>(cutout.atLast()).base(), -8.0f);
            cutout.add(std::move(c2_));
            
            Vec2 v1(-12, 35), v2(0, -52);
            Obround3D ob1_ = Obround3D(v1, v2, 23.5f)
                                        .setHeightRel(mainTop, -14.0f);
            cutout.add(std::move(ob1_));

            Cylinder c3_ = Cylinder(9.5f)
                            .setPosition2D(32.0f, 12.0f)
                            .setHeightRel(mainTop, -15.5f);
            
            cutout.add(std::move(c3_));

            Vec2 v3(2.3, -58), v4(22, -54);
            Obround3D ob2_ = Obround3D(v3, v4, 18.0f)
                                        .setHeightRel(mainTop, -15);
            cutout.add(std::move(ob2_));

            Cylinder c4_ = Cylinder(10.0f)
                            .setPosition2D(15.0f, 30.5f)
                            .setHeightRel(mainTop, -12.0f);
            cutout.add( std::move(c4_) );

            Vec2 v5(28, -31.5) ,v6(37, -48.5);
            Obround3D ob3_ = Obround3D(v5, v6, 9.0f)
                                        .setHeightRel(mainTop, -16.0f);
            cutout.add(std::move(ob3_));
            
            /*
            cutout.add<TruncatedCone>
            ( TruncatedCone(38.5,38).setPosXZ(51.5, -22).setTop(mainTop).setHeight(5) );
            cutout.add<Cylinder>
            ( Cylinder(30).setPosition(cutout[-1].position()).setTop(cutout[-1].base()).setHeight(4) );
            Vec2 v7(52.5, -20), v8(63.5, -20);
            cutout.add<Obround3D>
            ( Obround3D(0, 0).setLineLength(?).setRadius(12.5).setPosXZ((v7 + v8)/2.0).setTop(mainTop).setHeight(14).setRotation( calcAngle(v7, v8)) );
            cutout.add<Cylinder>
            ( Cylinder(9).setPosXZ(46, 28).setTop(mainTop).setHeight(13) );
            cutout.add<Cylinder>
            ( Cylinder(10).setPosXZ(39,35).setTop(mainTop).setHeight(14) );

            cutout.add<Sector3D>
            ( Sector3D(26, deg_to_rad(220), deg_to_rad(360)).setPosXZ(94.5, -28.5).setTop(mainTop).setHeight(9) );
            */
    }
}

#endif 