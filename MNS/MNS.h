/*
 *
 *
 *  Moe Neko Soft
 *  Role :Fonction de base pour moteur 3D
 *
 *  Kannagi
 *  g.strump@hotmail.fr
 *  kannagichan@gmail.com
 */


#ifndef MNS__LIB_GL
#define MNS__LIB_GL

#include "MNS_type.h"
#include "MNS_structure.h"
#include "MNS_GL_structure.h"

//FPS
void MNS_Fps(MNS_FPS *tim,int fps);


//Evenement
#if !defined( USE_GLFW )
MNS_event MNS_Evenement(void);
#else
typedef struct GLFWwindow GLFWwindow;
MNS_event MNS_Evenement( GLFWwindow * window );
#endif
void MNS_Evenement_init(void);
void MNS_Fenetre(int largeur,int hauteur,int fullscreen);
void MNS_Fenetre_redimension(float *radio);
void MNS_imp_ecran(char *dst);

//Camera
void MNS_Camera(MNS_CAMERA camera);
void MNS_Camera_Perspective(MNS_CAMERA camera);
void MNS_Camera_Ortho();
MNS_CAMERA MNS_Camera_Init(float radio);

void MNS_camera_vue_sub(MNS_CAMERA *camera,VEC3 *a,float v,int *touche);
void MNS_camera_vue_obj(MNS_CAMERA *camera,VEC3 *p,VEC3 *a,float v,float vit,int *touche);

//Animation
void MNS_bone_transition(MNS_Model3D *obj);
void MNS_bone_rotation(MNS_Model3D *obj);

//rendu
void MNS_draw_skeleton_sp(MNS_Model3D *obj,MNS_Anim3D anim);
void MNS_draw_skeleton(MNS_Model3D *obj);
void MNS_rendu(MNS_Model3D *obj);

//Loader
void MNS_Model_init(MNS_Model3D *obj);
MNS_Model3D *MNS_load_3D_obj(char *nom_du_fichier);
void MNS_load_3D_mtl(char *nom_du_fichier,CHAINE *name,int n);
MNS_Model3D *MNS_load_3D_smd(char *nom_du_fichier);
MNS_Model3D *MNS_load_3D_bcm(char *nom_du_fichier);
MNS_Anim3D *MNS_load_3D_anim(char *nom_du_fichier);
MNS_Model3D* MNS_load_3D(char *adresse);
void MNS_load_texture_tab(MNS_Model3D *obj,char *dossier);

//Image
MNS_image *MNS_load_bmp(const char *adresse);
MNS_image *MNS_load_png(const char *adresse);
MNS_image *MNS_load_pcx(const char *adresse);
MNS_image *MNS_load_jpeg(const char *adresse);
MNS_image* MNS_load(const char *adresse);

void MNS_save_bitmap(MNS_image *image,char *adresse);

//Texture
void MNS_affichage_texture(MNS_image *image);
void MNS_affiche_texture(MNS_image *image);
void MNS_load_texture(MNS_image *image,int *id);
void MNS_delete_texture(int *id);

//fonction 2D
void MNS_blit(MNS_RECT tile,MNS_RECTF *t,VEC2 p);
void MNS_DrawArray(float *v,float *vt,int nf);

//Free
void MNS_free(MNS_image *image);

//Lecture de fichier
short read_type_short(FILE *fichier);
long read_type_long(FILE *fichier);
float read_type_float(FILE *fichier);

void write_type_short(FILE *fichier,short itype);
void write_type_long(FILE *fichier,long itype);
void write_type_float(FILE *fichier,float g);

//Script
void MNS_dossier_out(char *nom_du_fichier,char *dossier);
void MNS_lecture_chaine(char *chaine,char *ch,int nbr);
int MNS_lecture_chaine_ext(char *chaine,char *ch,int nbr,char no);

#endif
