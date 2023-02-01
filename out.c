
#line 42 "test.xml"

				
#line 43 "test.xml"

#line 54 "test.xml"

				#include <stdio.h>
				#include <ctype.h>
				#include "fstio.h"
				#include "xarr.h"
				#include "trie_map.h"
				#include <libxml/parser.h>
			
#line 43 "test.xml"

				
#line 44 "test.xml"

#line 66 "test.xml"

			
#line 101 "test.xml"

					struct string;
				
#line 107 "test.xml"

					DEFINE_XARR(string, char);
				
#line 228 "test.xml"

						struct string compress_ws (struct string string);
					
#line 301 "test.xml"

						struct strings;
					
#line 1023 "test.xml"

				struct string_or_insert;
			
#line 1062 "test.xml"

				struct string_or_insert_sequence;
			
#line 1088 "test.xml"

				enum deftext_resolution_state;
			
#line 1122 "test.xml"

				struct deftext_data;
			
#line 1248 "test.xml"

				struct id_deftext_map;
			
#line 44 "test.xml"

				
#line 45 "test.xml"

#line 234 "test.xml"

						struct string
						compress_ws (struct string string) {
							struct string result = string_make ();
							
#line 238 "test.xml"

#line 249 "test.xml"

						bool prev_was_ws = false;
					
#line 252 "test.xml"

						for (char *ch = string.front; ch != string.back; ch++)
					
#line 259 "test.xml"

						{
					
#line 262 "test.xml"

						if (!isspace (*ch))
						{
							string_insert (&result, *ch);
							prev_was_ws = false; 
						}
					
#line 280 "test.xml"

						else
						{
							if (!prev_was_ws)
							{
								string_insert (&result, ' ');
							}
							prev_was_ws = true;
						}
					
#line 291 "test.xml"

						}
					
#line 238 "test.xml"

							return result;
						}
					
#line 306 "test.xml"

						DEFINE_XARR(strings, struct string);
					
#line 1029 "test.xml"

				struct string_or_insert
				{
			
#line 1036 "test.xml"

				int is_insert;
			
#line 1042 "test.xml"

				union
				{
					struct string literal_string;
					struct string insertion_id;
				};
			
#line 1050 "test.xml"

				};
			
#line 1068 "test.xml"

				DEFINE_XARR(string_or_insert_sequence, struct string_or_insert);
			
				enum deftext_resolution_state
				{
					deftext_unresolved,
					deftext_resolving,
					deftext_resolved
				};
			
#line 1130 "test.xml"

				struct deftext_data
				{
			
#line 1135 "test.xml"

				struct string id;
			
#line 1140 "test.xml"

				struct string_or_insert_sequence body;
			
#line 1145 "test.xml"

				struct string resolution;
			
#line 1149 "test.xml"

				enum deftext_resolution_state resolution_state;
			
#line 1155 "test.xml"

				struct string file;
			
#line 1159 "test.xml"

				};
			
#line 1254 "test.xml"

				DEFINE_STRING_MAP(id_deftext_map, struct deftext_data);
			
#line 45 "test.xml"

				
#line 46 "test.xml"

#line 46 "test.xml"

				
#line 47 "test.xml"

#line 79 "test.xml"

				/* begin function declarations */
			
#line 123 "test.xml"

						struct string from_sz (const char *sz);
					
#line 160 "test.xml"

						char *to_sz (struct string string);
					
#line 205 "test.xml"

						void
						string_append (struct string *to, struct string from);
					
						struct string string_copy(struct string src);
					
						struct strings strings_copy(struct strings src);
					
#line 369 "test.xml"

				int
				xml_tangle (xmlDocPtr xml_document);
			
#line 1185 "test.xml"

				struct deftext_data
				deftext_data_make_empty ();
			
#line 1303 "test.xml"

				void c_processor(xmlDocPtr doc);
			
#line 1421 "test.xml"

				void replace_special_chars(xmlDocPtr doc);
			
#line 1570 "test.xml"

				void context_query(xmlDocPtr doc, char *queryid);
			
#line 47 "test.xml"

				
#line 48 "test.xml"

#line 86 "test.xml"

				/* begin function definitions */
			
#line 129 "test.xml"

						struct string
						from_sz (const char *sz)
						{
							struct string string = string_make ();
							
#line 134 "test.xml"

#line 144 "test.xml"

						for (; *sz; sz++)
						{
							string_insert (&string, *sz);
						}
					
#line 134 "test.xml"

							return string;
						}
					
#line 167 "test.xml"

						char *
						to_sz (struct string string)
						{
							char *sz = malloc (string.len + 1);
							
#line 172 "test.xml"

#line 183 "test.xml"

						int i = 0;
					
#line 188 "test.xml"

						for (char *ch = string.front; ch != string.back; ch++, i++)
						{
							sz[i] = *ch;
						}
					
#line 195 "test.xml"

						sz[string.len] = 0;
					
#line 172 "test.xml"

							return sz;
						}
					
#line 212 "test.xml"

						void
						string_append (struct string *to, struct string from) {
							for (char *ch = from.front; ch != from.back; ch++) {
								string_insert (to, *ch);
							}
						}
					
						struct string string_copy(struct string src) {
							struct string dst = string_make();
							for (char *srcc = src.front; srcc != src.back; srcc++)
								string_insert(&dst, *srcc);
							return dst;
						}
					
						struct strings strings_copy(struct strings src) {
							struct strings dst = strings_make();
							for (struct string *srcstr = src.front; srcstr != src.back; srcstr++) {
								strings_insert(&dst, string_copy(*srcstr));
							}
							return dst;
						}
					
#line 377 "test.xml"

				int
				xml_tangle (xmlDocPtr xml_document)
				{
				
#line 381 "test.xml"

#line 404 "test.xml"

			struct id_deftext_map *id_deftext_map = id_deftext_map_new ();
		
#line 408 "test.xml"

			
#line 409 "test.xml"

#line 438 "test.xml"

			void
			dfs_search_deftexts(xmlNodePtr current_node) {
				if (current_node->type == XML_ELEMENT_NODE) {
					if (!xmlStrcmp(current_node->name, (const xmlChar *) "deftext")) {
						
#line 443 "test.xml"

#line 468 "test.xml"

			const xmlChar *id = xmlGetProp (current_node, "id");
		
#line 475 "test.xml"

			if (id != NULL)
			{
				
#line 478 "test.xml"

#line 496 "test.xml"

			const xmlChar *file_sz = xmlGetProp(current_node, "file");
		
#line 501 "test.xml"

			struct string file_str = file_sz != NULL? from_sz (file_sz) : string_make ();
		
#line 506 "test.xml"

			struct deftext_data *deftext_data = NULL;
		
#line 511 "test.xml"

			
#line 512 "test.xml"

#line 665 "test.xml"

			struct deftext_data default_value() {
				struct deftext_data v = deftext_data_make_empty ();
		
#line 674 "test.xml"

			assert (v.id.len == 0);
			assert (v.id.front);
			free (v.id.front);
			v.id = from_sz (id);
		
#line 681 "test.xml"

			assert (v.file.len == 0);
			assert (v.file.front);
			free (v.file.front);
			v.file = file_str;
		
#line 688 "test.xml"

			assert (v.body.front != NULL);
			assert (v.body.len == 0);
		
#line 693 "test.xml"

			assert (v.resolution.front != NULL);
			assert (v.resolution.len == 0);
		
#line 698 "test.xml"

			assert (v.resolution_state == deftext_unresolved);
		
#line 704 "test.xml"

				return v;
			}
		
#line 714 "test.xml"

			deftext_data = id_deftext_map_get(id_deftext_map, id, id + strlen(id), default_value);
		
#line 512 "test.xml"

			assert(deftext_data != NULL);
		
#line 517 "test.xml"

			for (xmlNodePtr child = current_node->children; child != NULL; child = child->next)
			if (child->type == XML_ELEMENT_NODE && !xmlStrcmp(child->name, (const xmlChar *) "reftext"))
			{
		
#line 526 "test.xml"

			for (xmlNodePtr reftext_child = child->children; reftext_child != NULL; reftext_child = reftext_child->next)
			{
		
#line 533 "test.xml"

			if (reftext_child->type == XML_TEXT_NODE)
			{
				
#line 536 "test.xml"

#line 574 "test.xml"

			struct string text = from_sz(reftext_child->content);
		
#line 578 "test.xml"

			struct string_or_insert wrapped_text;
			wrapped_text.is_insert = false;
			wrapped_text.literal_string = text;
		
#line 584 "test.xml"

			string_or_insert_sequence_insert (&deftext_data->body, wrapped_text);
		
#line 536 "test.xml"

			}
			else if (reftext_child->type == XML_ELEMENT_NODE && 
				!xmlStrcmp(reftext_child->name, (const xmlChar *) "insert"))
			{
				
#line 541 "test.xml"

#line 604 "test.xml"

			const xmlChar *text_id = xmlGetProp(reftext_child, "text");
		
#line 608 "test.xml"

			if (text_id == NULL)
			{
				fprintf (stderr, "At line %d: Insert without text attribute\n", reftext_child->line);
			}
		
#line 615 "test.xml"

			else
			{
		
#line 621 "test.xml"

			struct string text_id_str = from_sz (text_id);
		
#line 625 "test.xml"

			struct string_or_insert wrapped_insert;
			wrapped_insert.is_insert = true;
			wrapped_insert.insertion_id = text_id_str;
		
#line 631 "test.xml"

			string_or_insert_sequence_insert (&deftext_data->body, wrapped_insert);
		
#line 635 "test.xml"

			}
		
#line 541 "test.xml"

			}
			else
			{
				// ignore it.
			}
		
#line 549 "test.xml"
 
			}
		
#line 553 "test.xml"

			}
		
#line 478 "test.xml"

			}
		
#line 443 "test.xml"

					}
					for (xmlNodePtr child = current_node->children; 
						child != NULL; 
						child = child->next) {
						dfs_search_deftexts (child);
					}
				}
			}
		
#line 456 "test.xml"

			dfs_search_deftexts (xmlDocGetRootElement (xml_document));
		
#line 409 "test.xml"

		
#line 412 "test.xml"

			
#line 413 "test.xml"

#line 729 "test.xml"

			struct string
			resolve_deftext(struct string id)
			{
			
#line 733 "test.xml"

#line 827 "test.xml"

			struct deftext_data *data = id_deftext_map_search(id_deftext_map, id.front, id.back);
			if (data == NULL)
			{
				fprintf (stderr, "Warning: Resolved non existent %.*s to an empty string\n", id.len, id.front);
				return string_null ();
			}
			assert (data != NULL);
		
#line 838 "test.xml"

			switch (data->resolution_state)
			{
			case deftext_unresolved:
			
#line 842 "test.xml"

#line 899 "test.xml"

			data->resolution_state = deftext_resolving;
		
#line 906 "test.xml"

			assert (data->resolution.len == 0);
			assert (data->resolution.front == data->resolution.back);
			assert (data->resolution.front != NULL);
		
#line 918 "test.xml"

			for (struct string_or_insert *component = data->body.front;
				component != data->body.back;
				component++)
			{
				if (component->is_insert)
				{
					
#line 925 "test.xml"

#line 972 "test.xml"

			struct string insert_id = component->insertion_id;
		
#line 976 "test.xml"

			struct string insert_resolution = resolve_deftext(insert_id);
		
#line 984 "test.xml"

			if (data->resolution_state == deftext_resolved)
			{
				assert (data->resolution.front == NULL);
				assert (data->resolution.back == NULL);
				assert (data->resolution.len == 0);
				return data->resolution;
			}
		
#line 995 "test.xml"

			string_append (&data->resolution, insert_resolution);
		
#line 925 "test.xml"

				}
				else
				{
					string_append (&data->resolution, component->literal_string);
				}
			}
		
#line 943 "test.xml"

			data->resolution_state = deftext_resolved;
		
#line 949 "test.xml"

			return data->resolution;
		
#line 842 "test.xml"

			break;
			case deftext_resolving:
			
#line 845 "test.xml"

#line 871 "test.xml"

			data->resolution_state = deftext_resolved;
			assert (data->resolution.front);
			free (data->resolution.front);
			data->resolution = string_null ();
			fprintf (stderr, "Error: Insert cycle started at %.*s\n", id.len, id.front);
			return data->resolution;
		
#line 845 "test.xml"

			break;
			case deftext_resolved:
			return data->resolution;
			break;
			}
		
#line 733 "test.xml"

			}
		
#line 739 "test.xml"

			void
			walk_over_id_deftext_map(struct id_deftext_map *node)
			{
			assert(node != NULL);
			if (node->has_value)
			{
			struct deftext_data *node_data = &node->value;
			
#line 747 "test.xml"

#line 783 "test.xml"

			struct string file_attribute = node_data->file;
		
#line 789 "test.xml"

			if (file_attribute.len > 0)
			{
		
#line 794 "test.xml"

			struct string resolution = resolve_deftext(node_data->id);
		
#line 800 "test.xml"

			char *filename = to_sz (file_attribute);
			fprintf(stderr, "Writing into %s\n", filename);
			FILE *output = fopen (filename, "w");
			fwrite (resolution.front, 1, resolution.len, output);
			fclose (output);
			free (filename);
		
#line 809 "test.xml"

			}
		
#line 747 "test.xml"

			}
			for (int i = 0; i < 256; i++)
			{
			if (node->transition[i] != NULL)
			{
			walk_over_id_deftext_map(node->transition[i]);
			}
			}
			}
		
#line 759 "test.xml"

			walk_over_id_deftext_map(id_deftext_map);
		
#line 413 "test.xml"

		
#line 381 "test.xml"

				}
			
#line 1192 "test.xml"

				struct deftext_data
				deftext_data_make_empty ()
				{
			
#line 1198 "test.xml"

				struct deftext_data deftext_data;
			
#line 1206 "test.xml"

				deftext_data.id = string_make ();
			
#line 1212 "test.xml"

				deftext_data.body = string_or_insert_sequence_make ();
			
#line 1218 "test.xml"

				deftext_data.resolution = string_make ();
			
#line 1224 "test.xml"

				deftext_data.resolution_state = deftext_unresolved;
			
#line 1230 "test.xml"

				deftext_data.file = string_make ();
			
#line 1236 "test.xml"

				return deftext_data;
				}
			
#line 1308 "test.xml"

				void c_processor(xmlDocPtr doc)
				{
					
#line 1311 "test.xml"

#line 1311 "test.xml"

					
#line 1312 "test.xml"

#line 1329 "test.xml"

			void dfs(xmlNodePtr node) {
				if (node->type == XML_ELEMENT_NODE &&
					!xmlStrcmp(node->name, (const xmlChar*) "reftext") &&
					node->parent &&
					!xmlStrcmp(node->parent->name, (const xmlChar*) "deftext") &&
					xmlGetProp(node->parent, "lang") != NULL &&
					!xmlStrcmp(xmlGetProp(node->parent, "lang"), (const xmlChar *) "c")) {
					
#line 1337 "test.xml"

#line 1353 "test.xml"

			for (xmlNodePtr ch = node->children; ch; ch = ch->next) {
				int ln = ch->line;
				
#line 1356 "test.xml"

#line 1362 "test.xml"

				if (ch->type == XML_TEXT_NODE) {
					for (const xmlChar *txtc = ch->content; *txtc; txtc++) {
						if (*txtc == '\n') ln--;
					}
				}
				
#line 1368 "test.xml"

#line 1368 "test.xml"

				const char *ldfmt = "\n#line %d \"%s\"\n";
				
#line 1370 "test.xml"

#line 1370 "test.xml"

				int ldlen = snprintf(NULL, 0, ldfmt, ln, doc->URL);
				
#line 1372 "test.xml"

#line 1372 "test.xml"

				char *ld = malloc(ldlen + 1);
				snprintf(ld, ldlen + 1, ldfmt, ln, doc->URL);
				
#line 1375 "test.xml"

#line 1375 "test.xml"

				xmlNodePtr ldtxtn = xmlNewDocText(doc, (const xmlChar*) ld);
				xmlAddPrevSibling(ch, ldtxtn);
			}
		
#line 1337 "test.xml"

				}
				if (node->type == XML_ELEMENT_NODE)
					for (xmlNodePtr ch = node->children; ch; ch = ch->next)
						dfs(ch);
			}
			dfs(xmlDocGetRootElement(doc));
		
#line 1312 "test.xml"

					
#line 1313 "test.xml"

#line 1313 "test.xml"

				}
			
#line 1426 "test.xml"

				void replace_special_chars(xmlDocPtr doc) {
					
#line 1428 "test.xml"

#line 1453 "test.xml"

			xmlNodePtr dfs(xmlNodePtr node) {
				if (node->type == XML_ELEMENT_NODE && 
					node->prev &&
					node->prev->type == XML_TEXT_NODE) { 
#line 1457 "test.xml"

#line 1457 "test.xml"

					if (!xmlStrcmp(node->name, (const xmlChar *) "lt")) { 
#line 1458 "test.xml"

#line 1458 "test.xml"

						xmlNodeAddContent(node->prev, (const xmlChar *) "<");
						goto rm_node;
					} 
#line 1461 "test.xml"

#line 1461 "test.xml"
 else if (!xmlStrcmp(node->name, (const xmlChar *) "gt")) {
						xmlNodeAddContent(node->prev, (const xmlChar *) ">");
						goto rm_node;
					} else if (!xmlStrcmp(node->name, (const xmlChar *) "amp")) {
						xmlNodeAddContent(node->prev, (const xmlChar *) "&");
						goto rm_node;
					} else if (!xmlStrcmp(node->name, (const xmlChar *) "and")) {
						xmlNodeAddContent(node->prev, (const xmlChar *) "&&");
						goto rm_node;
					} else if (!xmlStrcmp(node->name, (const xmlChar *) "or")) {
						xmlNodeAddContent(node->prev, (const xmlChar *) "||");
						goto rm_node;
					}
					goto children_iteration;
					rm_node:
					xmlNodePtr nxt = node->next;
					if (nxt != NULL && nxt->type == XML_TEXT_NODE) {
						xmlNodePtr nxtnxt = nxt->next;
						int ln = nxt->line;
						xmlNodeAddContent(node->prev, nxt->content);
						node->prev->line = ln;
						xmlUnlinkNode(nxt);
						xmlFreeNode(nxt);
						nxt = nxtnxt;
					}
					xmlUnlinkNode(node);
					xmlFreeNode(node);
					return nxt;
				} 
#line 1489 "test.xml"

#line 1489 "test.xml"

				children_iteration:
				for (xmlNodePtr ch = node->children; ch != NULL; ch = dfs(ch));
				return node->next;
			}
			dfs(xmlDocGetRootElement(doc));
		
#line 1428 "test.xml"

				}
			
#line 1575 "test.xml"

				void context_query(xmlDocPtr doc, char *queryid) {
					
#line 1577 "test.xml"

#line 1588 "test.xml"

			
#line 1589 "test.xml"

#line 1637 "test.xml"

			DEFINE_STRING_MAP(ictxmap, struct strings);
			struct ictxmap *ictxmap = ictxmap_new();
		
#line 1650 "test.xml"

			DEFINE_STRING_MAP(inspmap, xmlNodePtr);
			struct inspmap *inspmap = inspmap_new();
		
#line 1662 "test.xml"

			DEFINE_STRING_MAP(cctxsmap, struct strings);
			struct cctxsmap *cctxsmap = cctxsmap_new();
		
#line 1589 "test.xml"

		
#line 1597 "test.xml"

			
#line 1598 "test.xml"

#line 1679 "test.xml"

			void dfs(xmlNodePtr cn) {
				if (cn->type == XML_ELEMENT_NODE &&
					!xmlStrcmp(cn->name, (const xmlChar*) "deftext")) {
					
#line 1683 "test.xml"

#line 1699 "test.xml"

			const xmlChar *cdid = xmlGetProp(cn, "id");
			int cdidlen = strlen(cdid);
		
#line 1706 "test.xml"

			if (cdid == NULL) {
				goto go_over_children;
			}
		
#line 1716 "test.xml"

			struct strings *cdctx = cctxsmap_get(cctxsmap, cdid, cdid + cdidlen, strings_make);
		
#line 1731 "test.xml"

			void cddfs(xmlNodePtr cdch) {
				if (!xmlStrcmp(cdch->name, (const xmlChar*)"deftext")) {
					return;
				} else if (!xmlStrcmp(cdch->name, (const xmlChar*)"insert")) {
					
#line 1736 "test.xml"

#line 1756 "test.xml"

			ictxmap_set(ictxmap, (char*)&cdch, (char *)&cdch + sizeof(xmlNodePtr), strings_copy(*cdctx));
		
#line 1764 "test.xml"

			const xmlChar *instxt = xmlGetProp(cdch, "text");
			if (instxt != NULL) {
				int instxtlen = strlen(instxt);
				inspmap_set(inspmap, instxt, instxt + instxtlen, cdch);
			}
		
#line 1736 "test.xml"

				} else if (!xmlStrcmp(cdch->name, (const xmlChar*)"cx")) {
					
#line 1738 "test.xml"

#line 1788 "test.xml"

			xmlNodePtr fch = cdch->children;
			if (fch != NULL && 
				fch->type == XML_TEXT_NODE) {
				struct string txt = from_sz(fch->content);
				strings_insert(cdctx, txt);
			}
		
#line 1738 "test.xml"

				} else if (!xmlStrcmp(cdch->name, (const xmlChar*)"ecx")) {
					
#line 1740 "test.xml"

#line 1811 "test.xml"

			if (cdctx->len) {
				free(cdctx->back[-1].front);
				cdctx->back--;
				cdctx->len--;
			} else {
				fprintf(stderr, "At line %d: ecx without context to pop\n", cdch->line);
			}
		
#line 1740 "test.xml"

				}
				for (xmlNodePtr cdchch = cdch->children; cdchch != NULL; cdchch = cdchch->next)
					cddfs(cdchch);
			}
			for (xmlNodePtr cdch = cn->children; cdch; cdch = cdch->next)
				cddfs(cdch);
		
#line 1683 "test.xml"

				}
				go_over_children:
				for (xmlNodePtr ch = cn->children; ch != NULL; ch = ch->next) {
					dfs(ch);
				}
			}
			dfs(xmlDocGetRootElement(doc));
		
#line 1598 "test.xml"

		
#line 1606 "test.xml"

			
#line 1607 "test.xml"

#line 1834 "test.xml"

			for (;;) {
				int queryidlen = strlen(queryid);
				
#line 1837 "test.xml"

#line 1839 "test.xml"

				xmlNodePtr *inspptr = inspmap_search(inspmap, queryid, queryid + queryidlen);
				
#line 1841 "test.xml"

#line 1844 "test.xml"

				if (inspptr == NULL) break;
				xmlNodePtr insp = *inspptr;
				
#line 1847 "test.xml"

#line 1850 "test.xml"

				struct strings* inspctx = ictxmap_search(ictxmap, (char*)&insp, (char*)&insp + sizeof(xmlNodePtr));
				if (inspctx != NULL) {
					for (struct string *str = inspctx->back; str != inspctx->front; str--) {
						struct string s = str[-1];
						fprintf(stdout, "* %.*s\n", s.len, s.front);
					}
				}
				xmlNodePtr inspp = insp->parent;
				if (inspp == NULL || xmlStrcmp(inspp->name, (const xmlChar*)"reftext")) {
					fprintf(stderr, "Bad insert at line %d\n", insp->line);
					break;
				}
				xmlNodePtr inspdeftext = inspp->parent;
				if (inspdeftext == NULL || xmlStrcmp(inspdeftext->name, (const xmlChar*)"deftext")) {
					fprintf(stderr, "Bad insert at line %d\n", insp->line);
					break;
				}
				char *inspdeftextid = xmlGetProp(inspdeftext, "id");
				if (inspdeftextid == NULL) break;
				queryid = inspdeftextid;
			}
		
#line 1607 "test.xml"

		
#line 1577 "test.xml"

				}
			
#line 1888 "test.xml"

				int main(int argc, char *argv[]) {
					if (argc <= 1) {
						fprintf(stderr, "Error: No input file.\n");
						return 1;
					}
					char *input_file = argv[1];
					xmlDocPtr doc = xmlReadFile (input_file, NULL, 0);
					if (doc == NULL) {
						fprintf(stderr, "There were errors reading %s\n", input_file);
						return 1;
					}
					replace_special_chars(doc);
					c_processor(doc);
					xml_tangle(doc);
					for (int i = 2; i < argc; i++) {
						if (!strcmp(argv[i], "ctx") && i + 1 < argc) {
							context_query(doc, argv[i + 1]);
							i++;
						}
					}
					return 0;
				}
			
#line 48 "test.xml"

			