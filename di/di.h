/*
 * di.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: serge78rus
 */

#ifndef DI_H_
#define DI_H_

#ifdef __cplusplus
extern "C"{
#endif

#if defined USR_TM0
void di_setup(const uint8_t *pinarr, uint8_t pinnum, bool ext_timer);
#else
void di_setup(const uint8_t *pinarr, uint8_t pinnum);
#endif
uint16_t di_get();
void di_update();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* DI_H_ */
