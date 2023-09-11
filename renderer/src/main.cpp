/*
 * renderer_sample.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: igkiou
 */

#include "renderer.h"

int main() {

	/*
	 * Initialize scattering parameters.
	 */
	const Float sigmaT = FPCONST(10.0);
	const Float albedo = FPCONST(0.9);
	const Float gVal = FPCONST(0.8);
	pfunc::HenyeyGreenstein *phase = new pfunc::HenyeyGreenstein(gVal);

	/*
	 * Initialize scene parameters.
	 */
	const Float iorMedium = FPCONST(1.0);
	const tvec::Vec3f mediumL(-FPCONST(1.25), -FPCONST(10.0), -FPCONST(10.0));
	const tvec::Vec3f mediumR(FPCONST(1.25), FPCONST(10.0), FPCONST(10.0));

	/*
	 * Initialize source parameters.
	 */
	const tvec::Vec3f rayOrigin(mediumL.x, FPCONST(0.0), FPCONST(0.0));
	const Float rayAngle = FPCONST(0.0);
	const tvec::Vec3f rayDir(std::cos(rayAngle), std::sin(rayAngle),
							FPCONST(0.0));
	const Float rayRadius = FPCONST(0.5);
	const Float Li = FPCONST(75000.0);
    std::cout << "aergaergfwerg";

	/*
	 * Initialize camera parameters.
	 */
	const tvec::Vec2f viewOrigin(FPCONST(0.0), FPCONST(0.0));
	const tvec::Vec3f viewDir(-FPCONST(1.0), FPCONST(0.0), FPCONST(0.0));
	const tvec::Vec3f viewY(FPCONST(0.0), FPCONST(0.0), -FPCONST(1.0));
	const tvec::Vec2f viewPlane(FPCONST(20.0), FPCONST(20.0));
	const tvec::Vec2f pathlengthRange(-FPCONST(1.0), -FPCONST(1.0));
	const tvec::Vec3i viewReso(128, 128, 1);

	/*
	 * Initialize rendering parameters.
	 */
	const int64 numPhotons = 5000000L;
	const int maxDepth = -1;
	const Float maxPathlength = -1;
	const bool useDirect = false;

	const med::Medium medium(sigmaT, albedo, phase);

	const scn::Scene scene(iorMedium, mediumL, mediumR,
						rayOrigin, rayDir, rayRadius, Li,
						viewOrigin, viewDir, viewY, viewPlane, pathlengthRange);

	photon::Renderer renderer(maxDepth, maxPathlength, useDirect);

	image::SmallImage img(viewReso.x, viewReso.y, viewReso.z);
	renderer.renderImage(img, medium, scene, numPhotons);

    // img.writeToFile('out.pfm');

	return 0;
}
