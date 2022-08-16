# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 11:26:04 by akoykka           #+#    #+#              #
#    Updated: 2022/08/16 16:36:38 by akoykka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_CHECKER = checker

SRC_LIST =	push_swap.c llist_functions.c llist_functions2.c operations.c\
			validator.c compare.c get_travel.c align_stack.c \
			utils.c structmaker.c simple_sort.c

#SRC_LIST += debug.c

SRC_LIST_CHECKER = checker.c c_llist_functions.c c_llist_functions2.c \
					c_push.c c_rotate.c c_rrotate.c c_swap.c c_utils.c \
					c_validator.c c_makestruct.c

OBJECT_LIST = $(SRC_LIST:%.c=%.o)
OBJECT_LIST_CHECKER = $(SRC_LIST_CHECKER:%.c=%.o)

COMPILER = gcc
INCLUDES = -I .
WWW = -Wall -Werror -Wextra
#WWW += Wconversion
FLAGS += -o
LIB = -lft -L./libft

all: $(NAME) $(NAME_CHECKER)

$(NAME): $(OBJECT_LIST) $(SRC_LIST) Makefile
	make -C libft/
	$(COMPILER) $(WWW) $(OBJECT_LIST) $(INCLUDES) $(FLAGS) $(NAME) $(LIB)

$(NAME_CHECKER): $(OBJECT_LIST_CHECKER) $(SRC_LIST_CHECKER) Makefile
	$(COMPILER) $(WWW) $(OBJECT_LIST_CHECKER) $(INCLUDES) $(FLAGS) $(NAME_CHECKER) $(LIB)

$(OBJECT_LIST_CHECKER): %.o:%.c Makefile
	gcc -c -g $< $(INCLUDES)

$(OBJECT_LIST): %.o:%.c Makefile
	gcc -c -g $< $(INCLUDES)

clean:
	@make clean -C libft/
	@rm -f $(OBJECT_LIST)
	@rm -f $(OBJECT_LIST_CHECKER)
	@echo "Object files removed"
fclean: clean
	make fclean -C libft/
	rm -f $(NAME)
	rm -f $(NAME_CHECKER)

norm:
	norminette $(SRC_LIST_CHECKER) $(SRC_LIST)

run:
	./$(NAME) 9 8 1 2 4 5 6 7

run40:
	./$(NAME) 9 0 -17 5 16 12 -4 -12 15 -9 -13 -19 -11 8 10 -7 13 3 19 17 14 -6 -14 1 4 20 -16 -5 6 -15 2 -20 -2 -10 7 18 11 -3 -1 -8


run100:
	./$(NAME) 436 481 1004 921 1147 693 507 471 378 562 797 950 542 1237 92 168 892 445 430 528 670 721 266 448 767 876 674 588 488 1061 282 38 960 665 390 292 574 394 279 423 392 726 27 515 821 420 1039 503 1017 719 159 534 602 201 1157 591 101 1084 1135 762 410 1087 277 567 800 29 918 184 83 680 13 879 1173 1076 1208 743 633 1137 227 1300 859 56 820 945 294 894 28 391 614 1290 1105 532 43 278 270 165 1279 45 102 1261

run250:
	./$(NAME) 388 230 1234 380 331 961 1011 1193 332 363 1086 839 206 652 519 581 747 894 1077 34 1203 1270 876 1132 1268 1230 420 1127 209 768 248 14 1128 1070 1117 44 1250 211 61 1007 122 1098 690 597 374 29 647 703 587 329 931 777 692 196 521 968 1290 572 948 439 1194 607 237 1105 766 721 530 969 739 527 1019 1185 407 701 252 883 631 1002 665 1174 352 403 1287 30 41 99 1226 17 809 770 1243 991 453 385 676 731 444 477 980 411 1277 171 778 1221 528 157 543 712 1024 993 536 1085 154 339 760 934 1093 992 309 557 910 585 190 466 148 265 819 315 262 442 677 1125 470 952 843 109 722 734 437 942 269 998 855 825 383 191 1099 472 205 849 412 103 21 933 251 1224 257 254 845 105 1178 897 790 140 593 943 1104 408 726 275 285 426 774 794 1172 1012 1082 1013 243 354 155 529 795 545 971 451 1183 906 419 850 752 233 36 91 165 965 239 1190 1102 1255 1126 808 911 944 1147 1136 872 807 596 905 340 1100 939 59 1181 40 1291 389 173 1046 814 152 1005 866 433 875 1120 1175 561 1153 454 292 610 588 293 181 37 490 1049 798 621 1297 1079 518 954 1143 1206 461 579 614

run300:
	./$(NAME) 1025 293 373 640 915 5 428 567 57 1077 295 331 1103 682 169 977 753 1105 1178 197 188 549 72 793 204 306 1230 1084 1159 942 256 668 1259 721 1148 26 973 1135 917 758 939 538 588 906 361 253 21 406 152 261 6 135 114 1046 770 1281 866 761 597 659 513 636 846 330 692 542 650 639 548 670 745 971 141 844 1207 64 1204 649 491 1222 1073 207 1052 420 180 1248 1128 1053 899 110 1237 1191 230 216 274 940 830 4 586 268 751 109 1291 765 235 547 673 1202 354 499 300 112 735 1273 964 240 1298 553 773 324 243 531 70 123 526 1258 849 712 663 1142 825 10 584 1210 1263 701 251 391 81 902 1164 749 1014 870 976 454 918 1208 965 1233 199 1249 103 888 716 1104 467 209 872 162 800 1190 45 425 279 1221 981 1183 927 265 86 1066 1153 685 310 565 953 950 937 277 992 798 512 97 127 1294 1262 1005 595 1226 887 679 78 264 159 997 1295 241 514 1100 616 603 1088 605 206 857 83 1141 1051 218 792 750 1018 288 408 591 258 856 666 89 1061 1143 730 1292 879 626 1211 921 108 1082 1261 882 247 1085 272 618 276 519 780 1102 154 410 55 417 365 1283 843 349 223 1133 1049 1257 570 149 1074 1118 833 684 1290 1121 1188 126 1274 601 1160 665 901 297 95 125 308 1033 724 190 325 68 351 1168 367 853 961 865 593 1127 503 1163 1266 655 769 393 741 610 359 760 958 747 850 355 1054 641

run350:
	./$(NAME) 304 922 26 246 813 616 395 328 519 730 548 372 752 524 520 688 579 334 559 414 6 789 7 147 24 570 485 311 1227 871 432 1224 925 899 487 342 1125 698 392 78 809 980 253 382 1049 627 864 226 863 906 112 667 565 379 530 1004 458 280 539 22 853 924 1121 628 816 250 895 1270 190 742 1072 607 941 127 83 535 1168 1066 830 509 911 705 841 297 651 860 984 510 267 1255 1293 337 1137 804 1202 217 148 218 464 849 1100 1040 384 587 896 1159 1229 260 325 542 156 987 1011 1195 243 774 70 1042 385 103 141 1200 943 115 408 82 974 1298 175 1120 1272 630 892 435 89 172 411 326 1187 474 206 1152 917 388 923 268 556 919 401 1210 658 897 754 269 477 889 1275 254 801 466 1161 407 1145 788 1030 745 154 913 1048 573 157 798 369 712 356 424 1280 1172 194 663 773 119 376 927 938 543 410 449 456 876 843 220 505 81 322 654 1276 2 465 1144 341 1020 757 475 439 647 19 1084 778 735 348 100 1253 793 35 890 803 65 1242 977 1032 176 1078 702 521 498 821 1016 932 976 766 929 707 780 915 370 302 378 1021 134 27 720 1148 847 1151 1204 332 52 949 1208 905 701 996 303 1036 528 1179 1035 264 784 973 760 1102 888 451 833 1158 1212 133 790 626 442 782 756 122 767 266 1067 1051 858 574 171 359 469 857 331 618 1061 110 1111 15 879 51 87 1096 839 716 859 159 67 18 969 815 307 659 605 1188 1027 522 188 516 831 484 779 71 197 179 247 504 589 971 397 262 406 313 1003 665 468 120 227 726 792 47 143 586 861 622 533 463 1249 1205 1294 1045 457 446 901 444 344 985 1264

run400:
	./$(NAME) 646 732 241 148 487 1050 53 773 829 134 943 11 1095 622 353 985 344 777 1016 412 896 155 542 714 755 778 948 178 1170 886 945 389 891 405 1230 809 973 501 243 567 464 447 930 1212 1145 608 90 227 1252 1117 612 403 1141 672 780 1166 14 13 1078 534 305 392 342 117 1257 545 1164 143 493 960 191 1127 444 761 1085 857 630 111 586 505 684 279 406 967 256 831 1134 404 723 578 126 441 174 157 909 851 234 483 96 600 756 188 137 944 858 470 1221 950 939 558 810 839 1161 955 1149 1277 1223 875 443 782 1055 8 255 649 596 1250 6 1097 597 824 162 30 526 876 952 689 1163 251 1247 796 260 932 741 678 100 1244 1068 456 330 620 953 681 233 163 1289 766 859 2 284 1090 393 1181 496 601 497 175 1184 395 159 856 1035 358 854 798 55 895 390 580 1048 669 890 313 660 821 870 63 1209 125 1118 652 1211 218 997 1121 996 616 1265 998 226 133 161 825 490 772 641 1219 1197 560 880 176 1174 35 804 685 460 1106 1214 1270 518 1239 992 1014 94 736 235 988 760 264 1151 351 918 993 633 735 66 1208 786 572 928 690 1091 889 549 881 544 494 1057 1280 707 285 838 1237 449 1256 548 656 835 559 1282 1018 1278 165 708 213 181 1266 180 1146 1099 1067 1072 657 198 219 900 921 873 574 1047 130 744 604 229 1262 1104 297 52 368 1178 292 848 849 759 1235 961 1129 40 51 121 377 60 594 940 86 563 951 1175 296 1051 519 129 484 152 653 357 396 550 171 834 254 1105 28 694 783 675 775 141 1287 1119 336 1059 696 1236 98 710 1002 1077 317 114 1092 942 88 1213 272 683 635 149 508 1283 595 415 757 207 247 274 591 107 1167 232 280 673 670 1102 318 79 807 862 1275 815 481 1079 110 625 146 1136 410 370 411 77 571 642 754 1254 273 1195 491 894 1269 186 1123 623 71 383 1291 414 1227 1073 1258 1139 740

run450:
	./$(NAME) 223 1049 476 257 1085 369 672 528 452 919 940 693 604 1274 622 708 343 1129 325 503 6 499 663 193 975 918 108 417 854 909 423 393 685 577 1237 760 1034 47 478 651 1065 749 104 1175 504 1013 1234 340 534 588 1106 932 848 969 68 377 716 1250 906 1089 1078 632 140 1075 634 262 1165 81 1208 291 336 1018 57 1185 542 644 1198 373 959 682 705 729 321 203 361 468 220 418 14 274 1222 732 1284 229 1195 400 833 1113 563 1169 1197 1270 363 194 624 153 842 724 454 830 307 292 496 414 92 635 1011 1008 1145 867 994 1216 1102 966 948 412 774 45 308 738 985 477 1093 16 870 125 79 384 789 800 128 770 920 516 801 509 1029 763 160 876 639 327 781 730 1091 642 296 381 847 1298 374 877 667 1164 721 748 758 645 1236 147 1043 1010 25 252 766 664 869 259 1062 342 566 670 253 879 30 1118 587 181 939 76 353 1277 411 599 904 370 832 681 619 1069 222 397 998 211 184 497 332 1116 234 69 668 97 826 698 440 50 543 341 43 605 540 882 48 312 1119 787 233 175 838 891 102 421 270 995 163 815 415 1160 127 439 494 537 546 890 558 1058 518 1015 176 750 1211 1224 351 44 676 37 359 1079 1094 631 212 1045 822 457 691 1187 398 1251 487 574 436 564 1209 216 1061 114 119 285 776 1296 172 790 465 715 629 311 388 706 924 795 954 42 1037 863 744 214 1042 182 852 554 136 522 690 785 593 573 952 1194 544 1269 1246 620 1200 627 1196 694 123 989 124 413 511 1017 936 422 318 1248 1177 1207 261 53 1054 736 324 391 151 737 630 360 777 429 731 133 303 725 427 479 40 7 1143 717 137 993 189 884 1199 263 866 1163 165 1009 1189 366 1255 883 221 1057 486 958 224 41 734 24 1105 225 557 129 1262 638 864 520 34 1040 395 930 199 1157 992 797 851 191 692 355 739 523 743 827 51 469 483 63 547 1144 844 98 290 208 218 1124 1122 756 1146 846 1026 533 150 961 213 449 956 1048 12 364 156 368 938 806 20 960 539 431 232 196 15 1291 357 825 963 783 134 1070 957 323 1280 653 299 595 1103 964 673 5
run499:
	./$(NAME) 340 272 467 490 213 450 413 352 325 128 410 425 230 10 52 422 500 388 345 25 317 288 65 282 227 328 185 310 458 292 206 459 275 485 202 205 456 60 475 161 90 486 187 465 8 298 341 261 469 26 291 333 364 208 166 45 218 383 319 250 13 40 297 346 225 235 219 435 137 148 343 302 169 24 134 144 160 72 274 172 87 376 360 22 55 418 473 479 285 278 143 430 154 358 79 156 482 140 85 239 86 441 279 318 244 197 399 347 29 429 159 251 62 438 265 232 138 192 395 7 39 366 270 281 311 404 308 217 223 363 495 122 326 461 344 201 381 424 77 75 415 59 109 142 42 68 273 168 204 313 21 61 464 211 481 375 237 175 49 417 371 382 256 114 491 242 96 56 167 403 139 483 51 478 229 163 94 421 178 107 180 120 73 210 373 353 462 332 280 245 102 129 252 426 327 36 149 335 380 105 254 173 260 212 471 53 322 23 284 66 390 146 349 176 255 71 412 50 268 15 304 240 402 377 394 396 389 329 309 106 246 480 195 243 474 130 136 188 181 124 28 27 165 207 384 30 269 369 43 484 147 78 103 209 378 264 470 132 263 355 241 152 277 359 194 385 222 489 88 339 164 100 306 472 386 104 69 253 367 190 271 440 299 330 151 266 407 293 83 182 231 420 434 191 449 494 220 323 171 294 433 334 336 113 290 3 398 397 63 248 193 357 41 91 362 247 455 316 57 428 477 19 216 406 179 174 112 283 457 496 118 131 354 183 37 97 257 126 374 238 324 487 305 437 58 476 405 300 17 20 361 258 436 350 6 342 466 432 33 448 312 416 47 189 153 451 401 14 4 141 387 11 203 236 499 391 233 111 92 121 170 331 234 419 393 84 276 228 351 12 89 296 110 224 135 133 125 400 177 48 215 184 54 35 249 31 295 74 1 370 287 431 497 117 307 80 365 76 427 145 408 498 453 82 259 460 492 101 162 338 446 368 320 64 423 157 356 198 18 321 67 98 221 127 38 262 289 93 314 155 158 214 337 267 70 116 44 301 186 32 439 226 468 411 2 99 454 199 315 348 46 150 9 444 392 443 81 414 379 445 196 115 108 442 488 119 409 5 463 200 493 372 123 16 286 34 452 95 447
run500:
	./$(NAME) 368 385 1298 1158 517 735 1202 840 341 1172 733 1068 122 64 715 372 1198 920 667 25 1096 58 645 1075 1007 712 707 601 308 1255 701 479 953 729 1195 15 968 747 705 905 1008 478 259 587 858 1112 1285 758 274 337 1064 746 493 537 180 323 222 490 967 36 228 636 1000 996 33 1034 833 558 859 975 775 63 108 331 1294 462 1264 498 457 855 912 789 1191 578 899 1272 997 993 409 199 1197 565 507 754 527 1283 947 12 728 282 852 564 2 201 1144 506 344 551 873 742 104 87 549 1286 355 1042 195 619 284 941 1194 468 292 1262 145 1243 936 1038 1081 750 1090 950 883 832 982 158 693 1269 139 419 1176 236 723 708 1278 349 78 220 1118 1054 1166 443 38 183 489 496 3 269 103 880 585 1281 906 1048 453 288 686 495 631 949 132 699 59 1077 91 99 694 300 734 748 1270 869 213 275 837 1066 962 1233 874 260 461 797 515 861 980 295 1241 487 646 1049 1193 354 784 911 862 130 600 77 1135 576 704 738 147 535 900 20 897 445 605 958 439 296 945 1167 232 1220 794 73 916 969 230 960 553 328 164 584 1080 93 448 946 1001 66 1105 924 1181 977 426 114 216 894 264 1149 1031 896 805 400 1027 571 129 692 819 811 189 1246 718 617 438 1159 424 402 948 592 881 276 612 408 120 358 1292 625 1235 140 974 378 105 376 1187 695 460 1161 841 172 185 192 65 544 510 30 660 664 599 253 261 983 767 249 215 1010 1072 154 768 570 81 829 1247 128 651 1085 566 1032 815 1123 1252 1076 1216 778 650 724 1227 113 1171 807 610 473 384 687 72 703 271 456 1237 121 529 301 1288 892 330 516 40 978 836 973 388 1014 351 1275 267 491 963 1160 672 1145 233 502 61 1256 563 18 174 159 252 1046 1 310 596 193 568 543 662 533 29 682 316 799 882 350 929 762 847 908 866 1051 1230 943 1148 774 647 1078 937 1052 171 84 1177 34 1119 212 685 990 137 589 511 1130 1101 294 666 1234 630 227 879 1182 714 696 245 1261 1257 394 1108 798 613 152 464 1221 279 335 817 234 633 638 190 1165 98 671 1029 240 465 1169 314 1023 952 808 452 512 342 560 246 1174 1151 353 548 123 595 618 440 1250 698 420 425 186 281 447 1114 923 184 588 411 751 141 32 386 455 1215 1117 1266 92 1265 1251 644 961 994 904 293 875 209 769 1152 28 1071 6 157 1150

lldb:
	lldb push_swap

re: fclean all
