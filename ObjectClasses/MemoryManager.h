/*
 * MemoryManager.h
 *
 *  Created on: Jul 30, 2013
 *      Author: kons
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include "Object.h"
#include "ClassObject.h"
#include <vector>

using std::vector;
namespace traceGen {

class MemoryManager {
public:
	MemoryManager();
	virtual ~MemoryManager();
	int allocateObjectToRootset(int size, int threadNumber, int rootSetNumber, int maxPointers,int creationDate);
	int allocateObject(int size, int maxPointers, Object* creatorObject, int pointerIndex, int creationDate);
	Object* allocateObjectNew(int threadNumber, int maxPointers,int creationDate, int classID, int primField);

	int setPointer(Object* startObject, int pointerIndex, Object* targetObject);
	int setRootPointer(int threadNumber, int rootSetNumber, Object* newObject);
	// overloading
	int setRootPointer(int threadNumber, Object* newObject);
	int deletePointer(Object* startObject, int pointerNumber);
	bool addExObjectToRootset(Object* obj, int threadNumber);
	void deleteRoot(int thread, int root);

	Object* getRoot(int threadNumber, int rootSlotNumber);
	Object* getObjectByID(int id);
	int isRoot(int thread, Object* obj);
	int getRootsetNumberByReference(int thread, Object* obj);
	void visualizeState();
	void setupObjects();
	void requestPromotion(Object* object);
	void requestDeletion(Object* object);

	// since root set size is not fixed
	int getRootsetSize(int threadNumber);
	void addObjectToRootset(Object* newObject, int threadNumber);
	void deleteEndFromRootset(int threadNumber);
	void deleteFromRootset(int threadNumber, int rootSlotNumber);
	bool isObjectInRoot(int thread, Object* obj);
	int getARandomObjectID();
	int getARandomObjectID(int thread);
	void buildClassTable(int nClass);
	void printClassTable(char *classfilename);
	inline ClassObject* getClassObject(int clsIndex){return classList[clsIndex];}

private:
	int getListSlot();
	int nextId;
	//two dimensional rootset [threadNum][rootsetSize]
	vector<vector<Object*> > rootset;
	//collection of all objects (dynamic)
	vector<Object*> objectList;

	vector<ClassObject*>classList;
};

} /* namespace gcKons */
#endif /* MEMORYMANAGER_H_ */
