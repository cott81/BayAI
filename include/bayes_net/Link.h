/*
 * Link.h
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#ifndef LINK_H_
#define LINK_H_

namespace bayes_net {

class Link: public graph::Edge {
public:
	Link();
	virtual ~Link();
};

} /* namespace bayes_net */

#endif /* LINK_H_ */
