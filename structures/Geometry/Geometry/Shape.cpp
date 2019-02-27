#include "Shape.h"
#include "Point.h"
#include "Segment.h"

Intersection::Intersection() : bufOfPoints(), bufOfSegments() {
}

Intersection::Intersection( const Intersection& i ) : bufOfPoints(i.bufOfPoints), bufOfSegments(i.bufOfSegments) {
}

size_t Intersection::GetNumberOfPoints() const {
	return bufOfPoints.GetSize();
}

size_t Intersection::GetNumberOfSegments() const {
	return bufOfSegments.GetSize();
}

Intersection& Intersection::operator=( const Intersection& i) {
	bufOfPoints = i.GetPoints();
	bufOfSegments = i.GetSegments();
	return *this;
}

CArray<Point> Intersection::GetPoints() const {
	return bufOfPoints;
}

CArray<Segment> Intersection::GetSegments() const {
	return bufOfSegments;
}

CArray<Point>& Intersection::GetLinkToBufOfPoints() {
	return bufOfPoints;
}

CArray<Segment>& Intersection::GetLinkToBufOfSegments() {
	return bufOfSegments;
}

void Intersection::AddIntersection( const Intersection& inter ) {
	size_t numberOfPoints = GetNumberOfPoints(), numberOfSegments = GetNumberOfSegments();
	for( size_t i = 0; i < inter.GetNumberOfPoints(); i++ ) {
		bool flag = true;
		for( size_t j = 0; j < numberOfPoints; j++ ) {
			if( bufOfPoints[j] == inter.GetPoints()[i] ) {
				flag = false;
			}
		}
		bufOfPoints.PushBack( inter.GetPoints()[i] );
	}
	for( size_t i = 0; i < inter.GetNumberOfSegments(); i++ ) {
		bool flag = true;
		for( size_t j = 0; j < numberOfSegments; j++ ) {
			if( bufOfSegments[j] == inter.GetSegments()[i] ) {
				flag = false;
			}
		}
		bufOfSegments.PushBack( inter.GetSegments()[i] );
	}
}