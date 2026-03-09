import type { PageLoad } from './$types';

const BACKEND_URL = 'http://localhost:8080';

export const load: PageLoad = async ({ fetch }) => {
  const res = await fetch(`${BACKEND_URL}/api/pages/demo`);

  if (!res.ok) {
    throw new Error(`Failed to load backend page config: ${res.status}`);
  }

  const page = await res.json();
  return { page };
};